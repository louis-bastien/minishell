/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:40:20 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/21 22:19:57 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	single_quotes(char **str, char **current, t_state *state)
{
	char	*end;

	end = ft_strchr(*current + 1, '\'');
	if (!end)
	{
		ft_error("Unclosed quote", state);
		*current += 1;
	}
	else
	{
		remove_char_from_string(*str, end - *str);
		remove_char_from_string(*str, *current - *str);
		*current += end - *current - 1;
	}
}

void	double_quotes(char **str, char **current, t_state *state)
{
	char	*end;

	end = ft_strchr(*current + 1, '\"');
	if (!end)
	{
		ft_error("Unclosed quote", state);
		*current += 1;
		return ;
	}
	remove_char_from_string(*str, end - *str);
	remove_char_from_string(*str, *current - *str);
	*current = expnvar(str, *current - *str, end - 1 - *current, state);
}

void	unquoted(char **str, char **current, t_token *token, t_state *state)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = *current;
	while (is_valid_env(tmp[i]))
		i++;
	*current = expnvar(str, *current - *str, i, state);
	if (ft_strlen(*str) == 0)
		remove_token(&state->token_list, token);
}

void	remove_char_from_string(char *str, int pos)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0 && pos < len)
		ft_memmove(str + pos, str + pos + 1, len - pos);
}
