/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 22:08:26 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/07 16:25:35 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char *str, t_state *state)
{
	printf("Fatal Error: %s\n", str);
	reset_all(state);
	free (state);
	state = NULL;
	clear_history();
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
			printf("Error: %s\n", state->error);
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
