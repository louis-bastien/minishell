/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:34:12 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/20 11:48:06 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec_builtin(t_state *state, t_command *cmd)
{
	int	exit_status;

	exit_status = 0;
	if (!ft_strncmp(state->cmd_list->command, "cd", 3))
		exit_status = minicd(state);
	else if (!ft_strncmp(state->cmd_list->command, "pwd", 4))
		exit_status = mini_pwd(state);
	else if (!ft_strncmp(state->cmd_list->command, "echo", 5))
		exit_status = mini_echo(state);
	else if (!ft_strncmp(state->cmd_list->command, "export", 7))
		exit_status = mini_export(state);
	else if (!ft_strncmp(state->cmd_list->command, "unset", 6))
		exit_status = mini_unset(state);
	else if (!ft_strncmp(state->cmd_list->command, "env", 4))
		exit_status = mini_env(state);
	else if (!ft_strncmp(state->cmd_list->command, "exit", 5))
		exit_status = mini_exit(state);
	else
		ft_error_exec(cmd->command, NOCMD, "Invalid builtin", state);
	if (exit_status)
		ft_error_exec(cmd->command, exit_status, "Execution error", state);
}
