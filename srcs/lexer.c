/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:50:48 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/24 23:09:46 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lexer(char *input, t_state *state)
{
	t_item	*item_list;
	t_item	*tmp;

	item_list = NULL;
	ft_lexer_reader(&item_list, input, state);
	tmp = item_list;
	while (tmp)
	{
		ft_tokenise(tmp);
		tmp = tmp->next;
	}
}

void	ft_lexer_reader(t_item **item_list, char *input, t_state *state)
{
	int		length;
	char	*item_str;
	char	*reader;
	int		i;

	length = 0;
	i = 0;
	reader = input;
	while (*reader)
	{
		while (*reader && is_whitespace(*reader))
			reader++;
		while (*reader && !is_whitespace(reader[length]))
			length++;
		item_str = strndup(reader, length);
		if (!item_str)
			ft_exit("(Lexer) Failed to malloc item_str\n", state);
		if (!add_item(&item_list, item_str))
			ft_exit("(Lexer) Failed to add item");
		reader += length;
		length = 0;
	}
}

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

void	tokenise(t_item *item)
{
	char	*str;

	str = item->str;
	if (ft_strlen(str) == 1)
	{
		if (*str == '|')
			item->token = PIPE;
		else if (*str == '<')
			item->token = INPUT;
		else if (*str == '>')
			item->token = OUTPUT;
		else
			item->token = WORD;
	}
	else if (ft_strlen(str) == 2)
	{
		if (*str == '<' && *(str + 1) == '<')
			item->token = HEREDOC;
		else if (*str == '>' && *(str + 1) == '>')
			item->token = APPEND;
		else
			item->token = WORD;
	}
	else
		item->token = WORD;
}
