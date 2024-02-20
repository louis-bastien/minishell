/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:28:05 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/20 12:01:59 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pre_executor(t_state *state)
{
	printf("num_cmds=%d\n", state->num_cmds);
	if (state->num_cmds == 1)
		one_cmd(state);
	else
	{
		ft_init_pipes(state);
//		multiple_cmd(state);
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
			ft_error("Error while forking process", state);
		if (pid == 0)
			exec_cmd(cmd, state);
		waitpid(pid, &status, 0);
	}
}
