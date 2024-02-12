/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:32:31 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/09 19:26:11 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_whitespaces(char **str)
{
	while (**str && is_whitespace(**str))
		(*str)++;
}

char	*handle_string(char **reader, t_state *state)
{
	char	*token_str;
	char	*current;
	int		i;
	bool	quoted;

	quoted = false;
	token_str = NULL;
	current = *reader;
	i = 0;
	while (*current && (is_validchar(*current) || quoted))
	{
		if (is_quote(*current) && !quoted)
			quoted = true;
		else if(is_quote(*current) && quoted)
			quoted = false;
		current++;
		i++;
	}
	token_str = ft_strndup(*reader, i);
	*reader += i;
	if (!token_str)
	{
		ft_error("Failed to malloc regular expression", state);
		return (NULL);
	}
	return (token_str);
}

char	*handle_token(char **reader, t_state *state)
{
	char	*token_str;

	token_str = NULL;
	if (is_single_token(*reader))
	{
		token_str = ft_strndup(*reader, 1);
		*reader += 1;
	}
	else if (is_double_token(*reader))
	{
		token_str = ft_strndup(*reader, 2);
		*reader += 2;
	}
	if (!token_str)
		ft_error("Failed to malloc single/double tokens", state);
	return (token_str);
}

char	*handle_quotes(char **reader, t_state *state)
{
	char	*token_str;

	token_str = NULL;
	if (is_single_token(*reader))
	{
		token_str = ft_strndup(*reader, 1);
		*reader += 1;
	}
	else if (is_double_token(*reader))
	{
		token_str = ft_strndup(*reader, 2);
		*reader += 2;
	}
	if (!token_str)
		ft_error("Failed to malloc single/double tokens", state);
	return (token_str);
}