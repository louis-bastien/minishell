/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 22:08:26 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/15 11:16:55 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_all(t_state *state)
{
	if (state)
	{
		if (state->error || state->data->cmd_error)
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
		state->to_stop = false;
		state->num_cmds = 0;
		clear_heredoc(state);
		state->data->last_pid = -1;
		state->data->childs = 0;
	}
	g_signal_received = 0;
}

void	free_data(t_data *data)
{
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

void	free_env(char ***env)
{
	free_doubleptr(*env);
	free(env);
}

void	put_exit_code(int error_num, t_state *state)
{
	if (!state->data->exit_status)
		state->data->exit_status = error_num;
}
