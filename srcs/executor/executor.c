/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:28:05 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/20 17:31:19 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_executor(t_state *state)
{
	t_command	*cmd;

	cmd = state->cmd_list;
	while (cmd)
	{
		if (cmd->is_builtin == true)
			ft_exec_builtin(cmd, state);
		else
			exec_cmd(cmd, state);
		cmd = cmd->next;
	}
	if (state->data->childs > 0)
		ft_waitpid(state);
}

void	exec_cmd(t_command *cmd, t_state *state)
{
	char	*path;
	int		pid;

	path = get_path(cmd, state);
	if (state->error)
		return ;
	pid = fork();
	if (pid < 0)
		ft_error_exec(cmd->command, -1, "Error forking process", state);
	else if (pid == 0)
	{
		make_dup(cmd, state);
		execve(path, cmd->args, state->data->env);
		ft_error_exec(cmd->command, EXIT_FAILURE, "Execution Failed", state);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (is_last(cmd, state))
			state->data->last_pid = pid;
		state->data->childs++;
	}
}

void	make_dup(t_command *cmd, t_state *state)
{
	int	code;

	code = 0;
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->fd_in, 0) == -1)
			ft_error_exec(cmd->command, code, "Failed to dup STDIN", state);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_out, 1) == -1)
			ft_error_exec(cmd->command, code, "Failed to dup STDOUT", state);
		close(cmd->fd_out);
	}
}

void	ft_waitpid(t_state *state)
{
	int	status;
	int	wait_pid;

	wait_pid = 1;
	status = 0;
	while (wait_pid > 0)
	{
		wait_pid = waitpid(-1, &status, 0);
		if (wait_pid == state->data->last_pid)
		{
			if (WIFEXITED(status))
				state->data->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				state->data->exit_status = 128 + WTERMSIG(status);
			else
				state->data->exit_status = 0;
		}
	}
}

// void	one_cmd(t_state *state)
// {
// 	t_command	*cmd;
// 	int			pid;
// 	int			status;

// 	cmd = state->cmd_list;
// 	if (cmd->is_builtin == true)
// 		ft_exec_builtin(state, cmd);
// 	else
// 	{
// 		pid = fork();
// 		if (pid < 0)
// 			ft_error_exec(cmd->command, -1, "Error forking process", state);
// 		if (pid == 0)
// 			exec_cmd(cmd, state);
// 		waitpid(pid, &status, 0);
// 	}
// }

