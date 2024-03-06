/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:35:13 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/06 13:22:23 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_state	*init_state(t_state *state)
{
	t_state	*new_state;

	new_state = (t_state *)malloc(sizeof(t_state));
	if (!new_state)
		ft_exit("Failed to malloc t_state", state);
	new_state->error = NULL;
	new_state->token_list = NULL;
	new_state->cmd_list = NULL;
	new_state->data = NULL;
	new_state->heredoc = 0;
	new_state->num_cmds = 0;
	return (new_state);
}

t_data	*init_data(t_state *state, char **envp)
{
	t_data	*new_data;

	new_data = malloc(sizeof(t_data));
	if (!new_data)
		ft_exit("Failed to malloc t_data", state);
	new_data->env = copy_env(envp);
	new_data->cmd_error = NULL;
	new_data->exit_status = 0;
	new_data->last_pid = -1;
	new_data->childs = 0;
	return (new_data);
}
