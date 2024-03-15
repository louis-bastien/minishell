/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:34:12 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/15 15:27:01 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_builtin(t_command *cmd, t_state *state, char ***env)
{
	int	exit_status;
	int	fd_out;

	exit_status = 0;
	if (state->num_cmds == 1)
		fd_out = cmd->fd_out;
	else
		fd_out = STDOUT_FILENO;
	if (!ft_strncmp(cmd->command, "cd", 3))
		exit_status = minicd(cmd, env);
	else if (!ft_strncmp(cmd->command, "pwd", 4))
		exit_status = mini_pwd(env, fd_out);
	else if (!ft_strncmp(cmd->command, "echo", 5))
		exit_status = mini_echo(cmd, fd_out);
	else if (!ft_strncmp(cmd->command, "export", 7))
		exit_status = mini_export(cmd, env, fd_out);
	else if (!ft_strncmp(cmd->command, "unset", 6))
		exit_status = mini_unset(cmd, env);
	else if (!ft_strncmp(cmd->command, "env", 4))
		exit_status = mini_env(cmd, env, fd_out);
	else if (!ft_strncmp(cmd->command, "exit", 5))
		exit_status = mini_exit(state, cmd);
	else
		ft_error_exec(cmd->command, NOCMD, "Invalid builtin", state);
	return (exit_status);
}
