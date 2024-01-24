/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 22:08:26 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/24 22:52:51 by lbastien         ###   ########.fr       */
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
		free (state);
	}
	printf("Exiting\n", str);
	exit(1);
}

void	free_items(t_item	*items)
{
	t_item	*tmp;

	tmp = items;
	while (tmp)
	{
		items = items->next;
		free_node(tmp);
		tmp = items;
	}
}

void	free_node(t_item *node)
{
	if (node)
	{
		free(node->str);
		free(node);
		node = NULL;
	}
}