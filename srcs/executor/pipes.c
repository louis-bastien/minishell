/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:52:41 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/27 12:36:33 by lbastien         ###   ########.fr       */
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
	printf("(parent) assiging pipes %s(%d) fd_out=%d,%s(%d) fd_in=%d\n", cmd->command, cmd->index, pipe_fds[1], cmd->next->command, cmd->next->index, pipe_fds[0]);
	if (pipe_fds[0] > 256)
	{
		ft_error_exec(cmd->command, 1, "Too many Pipes", state);
		close_open_fds(cmd, state);
		return (0);
	}
	if (cmd->fd_out == STDOUT_FILENO)
		cmd->fd_out = pipe_fds[1];
	else
	{
		close(pipe_fds[1]);
		printf("closing PIPE1\n");
	}
	if (cmd->next->fd_in == STDIN_FILENO)
		cmd->next->fd_in = pipe_fds[0];
	else
	{
		close(pipe_fds[0]);
		printf("closing PIPE2\n");
	}
	return (1);
}

void	make_dup(t_command *cmd, t_state *state)
{
	int	code;

	printf("(child %s%d) fd_in=%d fd_out=%d\n", cmd->command,cmd->index, cmd->fd_in, cmd->fd_out);
	code = 0;
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			ft_error_exec(cmd->command, code, "Failed to dup STDIN", state);
 		printf("(child%s%d) dupped fd_in (%d)\n", cmd->command, cmd->index, cmd->fd_in);
 		// printf("close value=%d\n", close(cmd->fd_in));
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			ft_error_exec(cmd->command, code, "Failed to dup STDOUT", state);
		printf("(child %s%d) dupped fd_out (%d)\n", cmd->command, cmd->index, cmd->fd_out);
		// printf("close value=%d\n", close(cmd->fd_out));
	}
	close_open_fds(cmd, state);
}

void	close_open_fds(t_command *cmd_child, t_state *state)
{
	t_command	*cmd;

	(void)state;
	cmd = cmd_child;
	while (cmd)
	{
		if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out >= 0)
			printf("(child %s%d) closing fd=%d, value=%d\n", cmd_child->command, cmd_child->index, cmd->fd_out, close(cmd->fd_out));
		if (cmd->fd_in != STDIN_FILENO && cmd->fd_in >= 0)
			printf("(child %s%d) closing fd=%d, value=%d\n", cmd_child->command, cmd_child->index, cmd->fd_in, close(cmd->fd_in));
		cmd = cmd->next;
	}
}

void	close_cmd_fds(t_command *cmd)
{
	if (cmd->fd_out != STDOUT_FILENO)
		printf("(parent) %s(%d) : closing fd_out(%d) (return=%d)\n", cmd->command, cmd->index, cmd->fd_out, close(cmd->fd_out));
	if (cmd->fd_in != STDIN_FILENO)
		printf("(parent) %s(%d) : closing fd_in(%d) (return=%d)\n", cmd->command, cmd->index, cmd->fd_in, close(cmd->fd_in));
}

