/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:29:59 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/04 15:59:52 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_token(t_token **token_list, char *str, t_ttype type)
{
	t_token	*tmp;
	t_token	*new_token;

	tmp = *token_list;
	new_token = create_token(str, type);
	if (!new_token)
		return (1);
	if (!tmp)
		*token_list = new_token;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
		new_token->prev = tmp;
	}
	return (0);
}

t_token	*create_token(char *str, t_ttype type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*import_tokens(t_token *tokens, int token_counter)
{
	t_token	*tokens_list;
	int		i;

	i = 0;
	tokens_list = NULL;
	while (i < token_counter)
	{
		add_token(&tokens_list, strdup(tokens->str), tokens->type);
		tokens = tokens->next;
		i++;
	}
	return (tokens_list);
}

void	remove_token(t_token **token_list, t_token *token)
{
	if (token->prev)
		token->prev->next = token->next;
	else
		*token_list = token->next;
	if (token->next)
		token->next->prev = token->prev;
	free_token(token);
}

int	count_token(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		i++;
		token = token->next;
	}
	return (i);
}
