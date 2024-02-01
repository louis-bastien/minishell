/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:18:17 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/01 16:19:34 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_expander(t_state *state)
{
	t_token	*token;

	token = state->token_list;
	while (token)
	{
		token->str = expand_env_variables(token->str, state);
		token = token->next;
	}
}

char	*expand_env_variables(char *str, t_state *state)
{
	char	*new_str;
	char	*current;
	char	*value;
	int		env_pos;

	current = str;
	while (*current)
	{
		if (*current == '$' && is_valid_env(*(current + 1)))
		{
			env_pos = current - str;
			value = get_env_value(current, state);
			new_str = replace_env(str, env_pos, value);
			if (!new_str)
				ft_exit("Failed to generate expanded string", state);
			free(str);
			str = new_str;
			current = str + env_pos;
		}
		current++;
	}
	return (str);
}

char	*replace_env(char *str, int env_pos, char *value)
{
	char	*new_str;
	int		new_length;
	int		name_length;

	name_length = ft_strlen(get_env_name(str + env_pos));
	new_length = ft_strlen(str) - (name_length) + ft_strlen(value);
	new_str = malloc(sizeof(char) * new_length);
	if (!new_str)
		return (NULL);
	strncpy(new_str, str, env_pos);
	new_str[env_pos] = '\0';
	strcat(new_str, value);
	strcat(new_str, str + env_pos + (name_length + 1));
	return (new_str);
}

int	is_valid_env(char c)
{
	if (ft_isalnum(c))
		return (1);
	else if (c == '?')
		return (1);
	else if (c == '_')
		return (1);
	else
		return (0);
}
