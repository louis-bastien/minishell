/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:34:12 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/21 13:05:03 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_builtin(t_command *cmd, t_state *state, char ***env)
{
	int	exit_status;
	int	fd_out;

	exit_status = 0;
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
		return (1);
	if (state->num_cmds == 1)
		fd_out = cmd->fd_out;
	else
		fd_out = STDOUT_FILENO;
	exit_status = exec_builtin(fd_out, cmd, state, env);
	return (exit_status);
}

int	exec_builtin(int fd_out, t_command *cmd, t_state *state, char ***env)
{
	int	exit_status;

	exit_status = 0;
	if (!ft_strncmp(cmd->command, "cd", 3))
		exit_status = minicd(cmd, env);
	else if (!ft_strncmp(cmd->command, "pwd", 4))
		exit_status = mini_pwd(env, fd_out);
	else if (!ft_strncmp(cmd->command, "echo", 5))
		exit_status = mini_echo(cmd, fd_out);
	else if (!ft_strncmp(cmd->command, "export", 7))
		exit_status = mini_export(cmd, state, env, fd_out);
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
