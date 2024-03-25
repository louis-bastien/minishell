/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:28:05 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/25 13:20:32 by lbastien         ###   ########.fr       */
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
			state->data->exit_status = handle_builtin(cmd, state, env);
		else if (cmd->command)
			exec_cmd(cmd, state, env);
		cmd = cmd->next;
	}
	if (state->data->childs > 0)
		ft_waitpid(state);
}

void	exec_cmd(t_command *cmd, t_state *state, char ***env)
{
	char	*tmp;

	tmp = NULL;
	if (is_absolute(cmd) == 1)
	{
		cmd->path = ft_strdup(cmd->command);
		tmp = ft_strrchr(cmd->command, '/') + 1;
		free(cmd->args[0]);
		cmd->args[0] = ft_strdup(tmp);
	}
	else if (!cmd->is_builtin)
		cmd->path = get_path(cmd, state, *env);
	if (!cmd->path && !cmd->is_builtin)
	{
		close_cmd_fds(cmd);
		return ;
	}
	fork_cmd(cmd, state, env);
}

void	fork_cmd(t_command *cmd, t_state *state, char ***env)
{
	int	pid;

	ft_signals(STOP);
	pid = fork();
	if (pid < 0)
		ft_error_exec(cmd->command, -1, "Error forking process", state);
	else if (pid == 0)
		ft_child(cmd, cmd->path, state, env);
	else
	{
		if (is_last(cmd, state))
			state->data->last_pid = pid;
		close_cmd_fds(cmd);
		state->data->childs++;
	}
	if (!cmd->is_builtin)
		free(cmd->path);
}

void	ft_child(t_command *cmd, char *path, t_state *state, char ***env)
{
	int		status;

	status = 0;
	ft_signals(EXEC);
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
		exit (1);
	make_dup(cmd, state);
	if (cmd->is_builtin == true)
	{
		status = handle_builtin(cmd, state, env);
		exit (status);
	}
	else
	{
		execve(path, cmd->args, *env);
		ft_error_exec(cmd->command, EXIT_FAILURE, "Execution Failed", state);
		exit(EXIT_FAILURE);
	}
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
				state->data->exit_status = status;
			else if (WIFSIGNALED(status))
			{
				if (status == SIGQUIT)
					write(1, "\n", 1);
				state->data->exit_status = status + 128;
			}
			else
				state->data->exit_status = 0;
		}
		state->data->childs--;
	}
}
