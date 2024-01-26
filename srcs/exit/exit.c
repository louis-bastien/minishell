/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 22:08:26 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/26 15:48:28 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(char *str, t_state *state)
{
	printf("Error: %s\n", str);
	if (state)
	{
		if (state->token_list)
			free_tokens (state->token_list);
		if (state->cmds)
			free_cmds (state->cmds);
		free (state);
		state = NULL;
	}
	printf("Exiting\n");
	exit(1);
}
