/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 22:08:26 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/20 17:20:23 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char *str, t_state *state)
{
	if (!state->error)
		state->error = ft_strdup(str);
	reset_all(state);
	if (state->data)
	{
		free_data(state->data);
		state->data = NULL;
	}
	free (state);
	state = NULL;
	clear_history();
	exit (1);
}

void	reset_all(t_state *state)
{
	if (state)
	{
		if (state->error)
			print_err(state);
		if (state->token_list)
		{
			free_tokens (state->token_list);
			state->token_list = NULL;
		}
		if (state->cmd_list)
		{
			free_cmds (state->cmd_list);
			state->cmd_list = NULL;
		}
		state->num_cmds = 0;
		state->data->last_pid = -1;
		state->data->childs = 0;
	}
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

void	free_data(t_data *data)
{
	if (data->env)
	{
		free_doubleptr(data->env);
		data->env = NULL;
	}
	free(data);
}

void	free_doubleptr(char **dptr)
{
	int	i;

	i = 0;
	while (dptr[i])
	{
		free(dptr[i]);
		i++;
	}
}
