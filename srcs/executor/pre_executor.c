/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:28:05 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/12 14:45:49 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exc_one_cmd(t_state *state)
{
	char	*path;

	path = get_path(state->data->path, state->cmd_list->command);
	if (path == NULL)
		ft_error_perm(NOCMD, state->cmd_list->command);
	execve(state->data->path, &state->cmd_list->command, state->data->env);
}

int	one_cmd(t_state *state)
{
	int	exit_code;
	int	pid;
	int	status;

	exit_code = 0;
	if (state->cmd_list->is_builtin == 0)
	{
		exit_code = ft_builtins(state);
		return (exit_code);
	}
	else
	{
		pid = fork();
		if (pid < 0)
			ft_error_sms("Error en fork");
		if (pid == 0)
			exc_one_cmd(state);
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) != 0)
			exit(WEXITSTATUS(status));
	}
	return (exit_code);
}

int	pre_executor(t_state *state)
{
	int	exit_code;

	if (state->data->pipes == 0)
		exit_code = one_cmd(state);
	else
	{
		exit_code = 0;
		printf("mas de un comando\n");
		//malloc de los pid
		//executor
	}
	return (exit_code);
}
