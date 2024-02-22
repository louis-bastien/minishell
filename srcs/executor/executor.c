/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:28:05 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/22 13:48:21 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_executor(t_state *state)
{
	t_command	*cmd;

	cmd = state->cmd_list;
	ft_init_pipes(state);
	while (cmd && !state->error)
	{
		if (cmd->is_builtin && state->num_cmds == 1)
			state->data->exit_status = ft_exec_builtin(cmd, state);
		else
			exec_cmd(cmd, state);
		cmd = cmd->next;
	}
	if (state->data->childs > 0)
		ft_waitpid(state);
}

void	exec_cmd(t_command *cmd, t_state *state)
{
	int		pid;

	if (state->error)
		return ;
	pid = fork();
	if (pid < 0)
		ft_error_exec(cmd->command, -1, "Error forking process", state);
	else if (pid == 0)
		ft_child(cmd, state);
	else
		ft_parent(cmd, pid, state);
}

void	ft_child(t_command *cmd, t_state *state)
{
	char	*path;
	int		status;

	status = 0;
	path = NULL;
//	printf("%s child process created\n", cmd->command);
	make_dup(cmd, state);
//	printf("%s executing...\n", cmd->command);
	if (cmd->is_builtin == true)
	{
		status = ft_exec_builtin(cmd, state);
		exit (status);
	}
	else
	{
		path = get_path(cmd, state);
		execve(path, cmd->args, state->data->env);
		ft_error_exec(cmd->command, EXIT_FAILURE, "Execution Failed", state);
		exit(EXIT_FAILURE);
	}
}

void	ft_parent(t_command *cmd, int pid, t_state *state)
{
//	printf("%s parent pid=%d fd_in=%d fd_out=%d\n", cmd->command, pid, cmd->fd_in, cmd->fd_out);
	if (is_last(cmd, state))
		state->data->last_pid = pid;
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	state->data->childs++;
}

void	ft_waitpid(t_state *state)
{
	int	status;
	int	wait_pid;

//	printf("Waitpid-childs=%d last_pid=%d\n", state->data->childs, state->data->last_pid);
	wait_pid = 1;
	status = 0;
	while (state->data->childs > 0)
	{
		wait_pid = waitpid(-1, &status, 0);
//		printf("%d process closed. Exit_status=%d\n", wait_pid, WEXITSTATUS(status));
		if (wait_pid == state->data->last_pid)
		{
			if (WIFEXITED(status))
				state->data->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				state->data->exit_status = 128 + WTERMSIG(status);
			else
				state->data->exit_status = 0;
		}
		state->data->childs--;
//		printf("Childs remaining=%d\n", state->data->childs);
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

