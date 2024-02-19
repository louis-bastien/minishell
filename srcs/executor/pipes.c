/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:52:41 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/19 18:07:45 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_pipes(t_state *state)
{
	t_command	*cmd;

	cmd = state->cmd_list;
	while (cmd && cmd->next)
	{
		if (needs_pipe(cmd))
		{
			if (!assign_pipes(cmd))
				ft_error("Failed to assign pipes", state);
		}
		cmd = cmd->next;
	}
}

int	needs_pipe(t_command *cmd)
{
	if (cmd->index == 1 || !cmd->next)
		return (1);
	else
		return (0);
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
	if (cmd->fd_in == STDIN_FILENO)
		cmd->fd_in = pipe_fds[0];
	else
		close(pipe_fds[0]);
	return (1);
}
