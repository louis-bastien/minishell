/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:04:09 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/19 18:02:35 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(char *str, t_state *state)
{
	if (!state->error)
		state->error = ft_strdup(str);
}

void	ft_error_exec(char *cmd, int exit_code, char *str, t_state *state)
{
	if (!state->error)
		state->error = ft_strdup(str);
	if (!state->data->exit_status)
		state->data->exit_status = exit_code;
	if (!state->data->exit_status)
		state->data->cmd_error = cmd;
}

void	print_error(t_state *state)
{
	if (state->data->cmd_error)
	{
		ft_putstr_fd(state->data->cmd_error, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(state->error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd("Error code: ", STDERR_FILENO);
	ft_putstr_fd(ft_itoa(state->data->exit_status), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(state->error);
	state->error = NULL;
	free(state->data->cmd_error);
	state->data->cmd_error = NULL;
}

void	ft_error_sms(char *str)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(str, 2);
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
		ft_putstr_fd(": command not found: ", 2);
		ft_putendl_fd(str, 2);
	}
	else if (perm == 42)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(str, 2);
	}
}
