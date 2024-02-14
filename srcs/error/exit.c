/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 22:08:26 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/14 14:03:44 by agheredi         ###   ########.fr       */
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

void	ft_error(char *str, t_state *state)
{
	if (!state->error)
		state->error = ft_strdup(str);
}

void	reset_all(t_state *state)
{
	if (state)
	{
		if (state->error)
		{
			ft_putstr_fd(state->error, STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			free(state->error);
			state->error = NULL;
		}
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
	}
}

void	free_data(t_data *data)
{
	if (data->env)
	{
		free_doubleptr(data->env);
		data->env = NULL;
	}
	if (data->path)
	{
		free_doubleptr(data->path);
		data->path = NULL;
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
