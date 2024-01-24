/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:50:48 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/24 19:48:07 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lexer(char *input)
{
	t_item	*item_list;
	t_item	*tmp;

	item_list = NULL;
	ft_lexer_reader(&item_list, input);
	tmp = item_list;
	while (tmp)
	{
		ft_tokenise(tmp);
		tmp = tmp->next;
	}
}

void	ft_lexer_reader(t_item **item_list, char *input)
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
			printf("Error mallocing item_str");
		add_item(&item_list, item_str);
		reader += length;
		length = 0;
	}
}

void	add_item(t_item **item_list, char *str)
{
	t_item	*tmp;
	t_item	*new_item;

	tmp = *item_list;
	new_item = create_item(str);
	if (!tmp)
		*item_list = new_item;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_item;
	}
}

t_item	*create_item(char *str)
{
	t_item	*item;

	item = malloc(sizeof(t_item));
	if (!item)
		printf("Failed to malloc item");
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
