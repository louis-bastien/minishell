/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:28:05 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/21 19:18:55 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_executor(t_state *state)
{
	t_command	*cmd;

	cmd = state->cmd_list;
	ft_init_pipes(state);
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
	printf("%s path is %s\n", cmd->command, path);
	if (state->error)
		return ;
	pid = fork();
	if (pid < 0)
		ft_error_exec(cmd->command, -1, "Error forking process", state);
	else if (pid == 0)
	{
		printf("%s child process created\n", cmd->command);
		make_dup(cmd, state);
		printf("%s executing...\n", cmd->command);
		execve(path, cmd->args, state->data->env);
		ft_error_exec(cmd->command, EXIT_FAILURE, "Execution Failed", state);
		printf("%s FAILED EXECUTION...\n", cmd->command);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (is_last(cmd, state))
		{
			state->data->last_pid = pid;
			printf("%s parent:is_last\n", cmd->command);
		}
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		state->data->childs++;
		printf("%s pid=%d\n", cmd->command, pid);
	}
}

void	make_dup(t_command *cmd, t_state *state)
{
	int	code;

	code = 0;
	if (cmd->fd_in != STDIN_FILENO)
	{
		printf("%s dupping fd_in (%d)\n", cmd->command, cmd->fd_in);
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			ft_error_exec(cmd->command, code, "Failed to dup STDIN", state);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		printf("%s dupping fd_out (%d)\n", cmd->command, cmd->fd_out);
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			ft_error_exec(cmd->command, code, "Failed to dup STDOUT", state);
		close(cmd->fd_out);
	}
}

void	ft_waitpid(t_state *state)
{
	int	status;
	int	wait_pid;

	printf("Waitpid-childs=%d last_pid=%d\n", state->data->childs, state->data->last_pid);
	wait_pid = 1;
	status = 0;
	while (state->data->childs > 0)
	{
		wait_pid = waitpid(-1, &status, 0);
		printf("%d process closed. Exit_status=%d\n", wait_pid, WEXITSTATUS(status));
		if (wait_pid == state->data->last_pid)
		{
			if (WIFEXITED(status))
				state->data->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				state->data->exit_status = 128 + WTERMSIG(status);
			else
				state->data->exit_status = 0;
			printf("Last pid found-Exit status=%d\n", state->data->exit_status);
		}
		state->data->childs--;
		printf("Childs remaining=%d\n", state->data->childs);
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

