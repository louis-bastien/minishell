/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:04:09 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/16 15:37:27 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char *str, t_state *state)
{
	int	exit_code;

	exit_code = state->data->exit_status;
	if (!state->error)
	{
		if (!str)
			state->error = NULL;
		else
			state->error = ft_strdup(str);
	}
	reset_all(state);
	if (state->data)
	{
		free_data(state->data);
		state->data = NULL;
	}
	free(state);
	state = NULL;
	clear_history();
	exit (exit_code);
}

void	ft_error(char *str, t_state *state)
{
	if (!state->error)
		state->error = ft_strdup(str);
	if (!state->data->exit_status)
		state->data->exit_status = 2;
}

void	ft_error_exec(char *cmd, int exit_code, char *str, t_state *state)
{
	if (!state->error)
		state->error = ft_strdup(str);
	if (!state->data->exit_status)
	{
		state->data->exit_status = exit_code;
	}
	if (!state->data->cmd_error)
		state->data->cmd_error = ft_strdup(cmd);
}


void	print_err(t_state *state)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	if (state->data->cmd_error)
	{
		ft_putstr_fd(state->data->cmd_error, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(state->error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(state->error);
	state->error = NULL;
	free(state->data->cmd_error);
	state->data->cmd_error = NULL;
}

void	ft_error_perm(int perm, char *str)
{
	if (perm == NOREAD || perm == NOWRITE)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (perm == 404)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (perm == NOCMD)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (perm == 42)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(str, 2);
	}
}
