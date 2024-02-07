/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:32:31 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/07 14:07:48 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_whitespaces(char **str)
{
	while (**str && is_whitespace(**str))
		(*str)++;
}

char	*handle_quotes(char **reader, t_state *state)
{
	char	*token_str;
	char	quote;
	int		i;

	printf("ENTERING3\n");
	quote = *(*reader)++;
	token_str = NULL;
	i = 0;
	while ((*reader)[i] && (*reader)[i] != quote)
		i++;
	if ((*reader)[i] != quote)
		ft_error("Unclosed quote", state);
	else
	{
		token_str = ft_strndup(*reader, i);
		if (!token_str && i)
			ft_error("Failed to malloc quoted token", state);
		(*reader)++;
	}
	return (token_str);
}

char	*handle_regular_expression(char *reader, t_state *state)
{
	char	*token_str;
	int		i;

	i = 0;
	while (reader[i] && is_validchar(reader[i]))
		i++;
	token_str = ft_strndup(reader, i);
	if (!token_str)
	{
		ft_error("Failed to malloc regular expression", state);
		return (NULL);
	}
	return (token_str);
}