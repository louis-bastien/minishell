/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:52:41 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/06 11:01:32 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_pipes(t_state *state)
{
	t_command	*cmd;

	cmd = state->cmd_list;
	while (cmd)
	{
		if (!assign_pipes(cmd))
			ft_error("Failed to assign pipes", state);
		cmd = cmd->next;
	}
}

int	assign_pipes(t_command *cmd)
{
	int	pipe_fds[2];

	if (cmd->next && needs_pipe(cmd))
	{
		if (pipe(pipe_fds) == -1)
			return (0);
		cmd->fd_out = pipe_fds[1];
		cmd->next->fd_in = pipe_fds[0];
		return (1);
	}
	else
		return (1);
}

int	needs_pipe(t_command *cmd)
{
	if (cmd->fd_out == STDOUT_FILENO && cmd->next->fd_in == STDIN_FILENO)
		return (1);
	else
		return (0);
}

void	make_dup(t_command *cmd, t_state *state)
{
	int	code;

	code = 0;
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			ft_error_exec(cmd->command, code, "Failed to dup STDIN", state);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			ft_error_exec(cmd->command, code, "Failed to dup STDOUT", state);
		close(cmd->fd_out);
	}
}
