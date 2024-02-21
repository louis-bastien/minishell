/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:18:17 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/21 22:24:35 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_expander(t_state *state)
{
	t_token	*token;
	t_token	*next_token;

	token = state->token_list;
	next_token = NULL;
	while (token)
	{
		next_token = token->next;
		quote_wrapper(token, state);
		token = next_token;
	}
}

void	quote_wrapper(t_token *token, t_state *state)
{
	char	*current;
	char	**str;

	current = token->str;
	str = &token->str;
	while (current && *current)
	{
		if (*current == '\'')
			single_quotes(str, &current, state);
		else if (*current == '\"')
			double_quotes(str, &current, state);
		else if (*current == '$' && is_valid_env(*(current + 1)))
			unquoted(str, &current, token, state);
		else
			current++;
	}
}

char	*expnvar(char **str, int start_pos, int len, t_state *state)
{
	char	*current;
	int		env_pos;
	char	*value;
	char	*new_str;
	char	*name;

	current = *str + start_pos;
	while (*current && --len && !is_quote(*current))
	{
		if (*current == '$' && is_valid_env(*(current + 1)))
		{
			env_pos = current - *str;
			name = get_env_name(current + 1, len);
			value = get_env_value(name, state);
			new_str = replace_env(*str, env_pos, value, name);
			if (!new_str)
				ft_error("Failed to generate expanded string", state);
			*str = new_str;
			current = new_str + env_pos + ft_strlen(value);
		}
		else
			current++;
	}
	return (current);
}
