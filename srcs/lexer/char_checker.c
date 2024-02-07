/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:30:38 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/07 13:39:41 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	if (c == 32)
		return (1);
	if (c >= 9 && c <= 13)
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	else
		return (0);
}

int	is_token(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

int	is_single_token(char *str)
{
	if (is_token(*str))
	{
		if (*str == '|')
			return (1);
		if (*str != str[1])
			return (1);
	}
	return (0);
}

int	is_double_token(char *str)
{
	if (is_token(*str))
	{
		if (*str == '|')
			return (0);
		if (*str == str[1])
			return (1);
	}
	return (0);
}

int	is_validchar (char c)
{
	if (is_token(c))
		return (0);
	else if (is_whitespace(c))
		return (0);
	else if (is_quote(c))
		return (0);
	else if (c != '$' && !ft_isalnum(c))
		return (0);
	else
		return (1);
}