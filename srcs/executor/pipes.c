/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:52:41 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/27 12:46:05 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_pipes(t_state *state)
{
	t_command	*cmd;

	cmd = state->cmd_list;
	while (cmd && cmd->next)
	{
		if (!assign_pipes(cmd, state))
			return ;
		cmd = cmd->next;
	}
}

int	assign_pipes(t_command *cmd, t_state *state)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		return (0);
	if (pipe_fds[0] > 256)
	{
		ft_error_exec(cmd->command, 1, "Too many Pipes", state);
		close_next_fds(state->cmd_list);
		return (0);
	}
	if (cmd->fd_out == STDOUT_FILENO)
		cmd->fd_out = pipe_fds[1];
	else
		close(pipe_fds[1]);
	if (cmd->next->fd_in == STDIN_FILENO)
		cmd->next->fd_in = pipe_fds[0];
	else
		close(pipe_fds[0]);
	return (1);
}

void	make_dup(t_command *cmd, t_state *state)
{
	int	code;

	code = 0;
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			ft_error_exec(cmd->command, code, "Failed to dup STDIN", state);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			ft_error_exec(cmd->command, code, "Failed to dup STDOUT", state);
	}
	close_next_fds(cmd);
}

void	close_next_fds(t_command *cmd)
{
	t_command	*current;

	current = cmd;
	while (current)
	{
		if (current->fd_out != STDOUT_FILENO && current->fd_out >= 0)
			close(current->fd_out);
		if (current->fd_in != STDIN_FILENO && current->fd_in >= 0)
			close(current->fd_in);
		current = current->next;
	}
}

void	close_cmd_fds(t_command *cmd)
{
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
}
