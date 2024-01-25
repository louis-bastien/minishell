/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:29:59 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/25 16:31:46 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_item(t_item **item_list, char *str)
{
	t_item	*tmp;
	t_item	*new_item;

	tmp = *item_list;
	new_item = create_item(str);
	if (!new_item)
		return (1);
	if (!tmp)
		*item_list = new_item;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_item;
	}
	return (0);
}

t_item	*create_item(char *str)
{
	t_item	*item;

	item = malloc(sizeof(t_item));
	if (!item)
		return (NULL);
	item->str = (str);
	item->next = NULL;
	return (item);
}

t_item	*import_items(t_item *tokens, int item_counter)
{
	t_item	*items_list;
	t_item	*tmp;
	int		i;

	i = 0;
	tmp = tokens;
	items_list = NULL;
	while (i < item_counter)
	{
		add_item(&items_list, strdup(tmp->str));
		tmp = tmp->next;
		i++;
	}
	return (items_list);
}
