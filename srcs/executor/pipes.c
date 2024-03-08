/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:52:41 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/07 16:10:56 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_pipes(t_state *state)
{
	t_command	*cmd;

	cmd = state->cmd_list;
	while (cmd && cmd->next)
	{
		if (!assign_pipes(cmd))
			ft_error("Failed to assign pipes", state);
		cmd = cmd->next;
	}
}

int	assign_pipes(t_command *cmd)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		return (0);
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
//		printf("%s : dupping fd_in\n", cmd->command);
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			ft_error_exec(cmd->command, code, "Failed to dup STDIN", state);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
//		printf("%s : dupping fd_out\n", cmd->command);
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			ft_error_exec(cmd->command, code, "Failed to dup STDOUT", state);
		close(cmd->fd_out);
	}
}
