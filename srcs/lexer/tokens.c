/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:29:59 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/26 11:53:16 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_token(t_token **token_list, char *str)
{
	t_token	*tmp;
	t_token	*new_token;

	tmp = *token_list;
	new_token = create_token(str);
	if (!new_token)
		return (1);
	if (!tmp)
		*token_list = new_token;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
	return (0);
}

t_token	*create_token(char *str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->next = NULL;
	return (token);
}

t_token	*import_tokens(t_token *tokens, int item_counter)
{
	t_token	*items_list;
	int		i;

	i = 0;
	items_list = NULL;
	while (i < item_counter)
	{
		add_item(&items_list, strdup(tokens->str));
		tokens = tokens->next;
		i++;
	}
	return (items_list);
}
