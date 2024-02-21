/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:52:41 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/21 17:49:05 by lbastien         ###   ########.fr       */
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
		printf("%s fd_in=%d fd_out=%d\n", cmd->command, cmd->fd_in, cmd->fd_out);
		cmd = cmd->next;
	}
}

int	assign_pipes(t_command *cmd)
{
	int	pipe_fds[2];

	if (cmd->next && needs_pipe(cmd))
	{
		printf("%s will be piped to next command\n", cmd->command);
		if (pipe(pipe_fds) == -1)
			return (0);
		cmd->fd_out = pipe_fds[1];
		cmd->next->fd_in = pipe_fds[0];
		return (1);
	}
	else
	{
		printf("%s will not be piped to next command\n", cmd->command);
		return (1);
	}
}

int	needs_pipe(t_command *cmd)
{
	if (cmd->fd_out == STDOUT_FILENO && cmd->next->fd_in == STDIN_FILENO)
		return (1);
	else
		return (0);

}
