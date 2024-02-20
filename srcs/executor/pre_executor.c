/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:28:05 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/20 15:30:29 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pre_executor(t_state *state)
{
	if (state->num_cmds == 1)
		one_cmd(state);
	else
	{
		ft_init_pipes(state);
		multiple_cmd(state);
	}
}

void	exec_cmd(t_command *cmd, t_state *state)
{
	char	*path;
	char	**all_path;

	all_path = ft_parse_path(state->data->env);
	path = get_path(all_path, cmd->command);
	if (path == NULL)
	{
		ft_error_exec(cmd->command, NOCMD, "Command does not exist", state);
		return ;
	}
	execve(path, state->cmd_list->args, state->data->env);
}

void	one_cmd(t_state *state)
{
	t_command	*cmd;
	int			pid;
	int			status;

	cmd = state->cmd_list;
	if (cmd->is_builtin == true)
		ft_exec_builtin(state, cmd);
	else
	{
		pid = fork();
		if (pid < 0)
			ft_error_exec(cmd->command, -1, "Error forking process", state);
		if (pid == 0)
			exec_cmd(cmd, state);
		waitpid(pid, &status, 0);
	}
}

void	multiple_cmd(t_state *state)
{
	t_command	*cmd;
	int			pid;
	int			last_pid;

	pid = -1;
	last_pid = -1;
	cmd = state->cmd_list;
	while (cmd)
	{
		pid = fork();
		if (pid < 0)
			ft_error_exec(cmd->command, -1, "Error forking process", state);
		if (pid == 0)
		{
			make_dup(cmd, state);
			exec_cmd(cmd, state);
		}
		if (is_last(cmd, state))
			last_pid = pid;
		cmd = cmd->next;
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

