/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:32:31 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/05 11:58:34 by lbastien         ###   ########.fr       */
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
	int		len;

	token_str = NULL;
	len = get_strlen(*reader);
	token_str = ft_strndup(*reader, len);
	*reader += len;
	if (!token_str)
	{
		ft_error("Failed to malloc regular expression", state);
		return (NULL);
	}
	return (token_str);
}

int	get_strlen(char *current)
{
	int		i;
	bool	quoted;
	char	quote_type;

	i = 0;
	quoted = false;
	while (*current && (is_validchar(*current) || quoted))
	{
		if (is_quote(*current) && !quoted)
		{
			quoted = true;
			quote_type = *current;
		}
		else if (*current == quote_type && quoted)
			quoted = false;
		current++;
		i++;
	}
	return (i);
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