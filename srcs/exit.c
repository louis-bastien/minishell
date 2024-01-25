/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 22:08:26 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/25 17:01:40 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(char *str, t_state *state)
{
	printf("Error: %s\n", str);
	if (state)
	{
		if (state->item_list)
			free_items (state->item_list);
		if (state->cmds)
			free_cmds (state->cmds);
		free (state);
		state = NULL;
	}
	printf("Exiting\n");
	exit(1);
}

void	free_cmds(t_command *cmds)
{
	t_command	*tmp;

	tmp = cmds;
	while (tmp)
	{
		cmds = cmds->next;
		free_cmd(tmp);
		tmp = cmds;
	}
}

void	free_items(t_item	*items)
{
	t_item	*tmp;

	tmp = items;
	while (tmp)
	{
		items = items->next;
		free_token(tmp);
		tmp = items;
	}
}
