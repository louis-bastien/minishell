/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:18:17 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/31 23:14:07 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_expander(t_state *state)
{
	t_token	*token;
	char	*new_str;

	token = state->token_list;
	while (token)
	{
		expand_env_variables(&token->str, state);
		token->str = new_str;
		token = token->next;
	}
}

char	*expand_env_variables(char **str, t_state *state)
{
	char	*start;
	char	*name;
	char	*value;
	char	*new_str;

	while (ft_strchr(str, '$'))
	{
		start = ft_strchr(str, '$');
		name = get_env_name(start);
		value = getenv(name);
		if (!value)
			value = "";
		new_str = replace_env(str, start - str, name, value);
		if (!new_str)
			ft_exit("Failed to generate expanded string", state);
		free (str);
		str = new_str;
	}
}

char	*replace_env(char *str, int start_pos, char *name, char *value)
{
	char	*new_str;
	int		new_length;

	new_length = ft_strlen(str) + ft_strlen(value) - ft_strlen(name) - 1;
	new_str = malloc(sizeof(char) * new_length + 1);
	strncpy(new_str, str, start_pos);
	new_str[start_pos] = '\0';
	ft_strcat(new_str + start_pos, value);
	ft_strcat(new_str, str + start_pos + ft_strlen(name));
	return (new_str);

}

char	*get_env_name(char *env)
{
	char	*start;
	char	*value;
	int		i;

	start = env + 1;
	i = 0;
	while (ft_isalnum(start[i]))
		i++;
	value = ft_strndup(start, i);
	return (value);
}