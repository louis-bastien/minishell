/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:34:12 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/28 10:39:21 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exec_builtin(t_command *cmd, t_state *state, char ***env)
{
	int	exit_status;

	exit_status = 0;
	//printf("entra en builtins\n");
	if (!ft_strncmp(cmd->command, "cd", 3))
		exit_status = minicd(cmd, env);
	else if (!ft_strncmp(cmd->command, "pwd", 4))
		exit_status = mini_pwd();
	else if (!ft_strncmp(cmd->command, "echo", 5))
		exit_status = mini_echo(cmd);
	else if (!ft_strncmp(cmd->command, "export", 7))
		exit_status = mini_export(cmd, env);
	else if (!ft_strncmp(cmd->command, "unset", 6))
		exit_status = mini_unset(cmd, env);
	else if (!ft_strncmp(cmd->command, "env", 4))
		exit_status = mini_env(cmd, env);
	else if (!ft_strncmp(cmd->command, "exit", 5))
		exit_status = mini_exit(state, cmd, env);
	else
		ft_error_exec(cmd->command, NOCMD, "Invalid builtin", state);
	if (exit_status)
		ft_error_exec(cmd->command, exit_status, "Execution error", state);
	return (exit_status);
}
