/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:28:05 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/16 20:43:54 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_executor(t_state *state, char ***env)
{
	t_command	*cmd;

	cmd = state->cmd_list;
	ft_init_pipes(state);
	while (cmd && to_continue(state))
	{
		if (cmd->is_builtin && state->num_cmds == 1)
			state->data->exit_status = ft_exec_builtin(cmd, state, env);
		else
			exec_cmd(cmd, state, env);
		cmd = cmd->next;
	}
	if (state->data->childs > 0)
		ft_waitpid(state);
}

void	exec_cmd(t_command *cmd, t_state *state, char ***env)
{
	int		pid;
	char	*path;
	char	*tmp;

	tmp = NULL;
	if (is_absolute(cmd) == 1)
	{
		path = ft_strdup(cmd->command);
		tmp = ft_strrchr(cmd->command, '/') + 1;
		free(cmd->args[0]);
		cmd->args[0] = ft_strdup(tmp);
	}
	else
		path = get_path(cmd, state, *env);
	if (!to_continue(state))
		return ;
	ft_signals(STOP);
	pid = fork();
	if (pid < 0)
		ft_error_exec(cmd->command, -1, "Error forking process", state);
	else if (pid == 0)
		ft_child(cmd, path, state, env);
	else
		ft_parent(cmd, pid, state);
}

void	ft_child(t_command *cmd, char *path, t_state *state, char ***env)
{
	int		status;

	status = 0;
	ft_signals(EXEC);
	make_dup(cmd, state);
	if (cmd->is_builtin == true)
	{
		status = ft_exec_builtin(cmd, state, env);
		exit (status);
	}
	else
		ft_execve(cmd, path, state, *env);
}

void	ft_parent(t_command *cmd, int pid, t_state *state)
{
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

	wait_pid = 1;
	status = 0;
	while (state->data->childs > 0)
	{
		wait_pid = waitpid(-1, &status, 0);
		if (wait_pid == state->data->last_pid)
		{
			if (WIFEXITED(status))
				put_exit_code(WEXITSTATUS(status), state);
			else if (WIFSIGNALED(status))
				put_exit_code(128 + WTERMSIG(status), state);
			else
				put_exit_code(0, state);
		}
		state->data->childs--;
	}
}
