/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:52:41 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/18 00:55:17 by lbastien         ###   ########.fr       */
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
	if (cmd->fd_out == STDOUT_FILENO && cmd->next->fd_in == STDIN_FILENO)
		return (1);
	else
		return (0);
}

int	assign_pipes(t_command *cmd)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		return (0);
	else
	{
		cmd->fd_out = pipe_fds[1];
		cmd->next->fd_in = pipe_fds[0];
		return (1);
	}
}