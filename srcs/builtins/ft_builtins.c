/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:34:12 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/09 20:42:36 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_builtins(t_state *state)
{
	int	exit_status;

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
	{
		printf("El argumento no es una builtin\n");
		exit_status = 2;
	}
	return (exit_status);
}
