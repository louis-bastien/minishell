/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:18:17 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/12 21:03:13 by lbastien         ###   ########.fr       */
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
	int		i;

	i = 0;
	current = token->str;
	str = &token->str;
	while (*current)
	{
		if (*current == '\'')
			parse_single_quotes(str, &current, state);
		else if (*current == '\"')
			parse_double_quotes(str, &current, state);
		else if (*current == '$' && is_valid_env(*(current + 1)))
		{
			while (is_valid_env(current[i]))
				i++;
			current = expnvar(str, 0, i, state);
			if (ft_strlen(*str) == 0)
			{
				remove_token(&state->token_list, token);
				break ;
			}
		}
		else
			current++;
	}
}

void	parse_double_quotes(char **str, char **current, t_state *state)
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

char	*expnvar(char **str, int start_pos, int len, t_state *state)
{
	char	*current;
	int		env_pos;
	char	*value;
	char	*new_str;
	char	*name;

	current = *str + start_pos;
	while (*current && --len)
	{
		if (*current == '$' && is_valid_env(*(current + 1)))
		{
			env_pos = current - *str;
			name = get_env_name(current + 1, len);
			value = get_env_value(name);
			new_str = replace_env(*str, env_pos, value, name);
			if (!new_str)
				ft_error("Failed to generate expanded string", state);
			free (name);
			free(*str);
			*str = new_str;
			current = new_str + env_pos + ft_strlen(value);
		}
		else if (is_quote(*current))
			break ;
		else
			current++;
	}
	return (current);
}

void	parse_single_quotes(char **str, char **current, t_state *state)
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
		printf("endpos=%ld, startpos=%ld\n", end - *str, *current - *str);
		remove_char_from_string(*str, end - *str);
		remove_char_from_string(*str, *current - *str);
	}
}

void	remove_char_from_string(char *str, int pos)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0 && pos < len)
		ft_memmove(str + pos, str + pos + 1, len - pos);
}

char	*replace_env(char *str, int env_pos, char *value, char *name)
{
	char	*new_str;
	int		new_length;
	int		name_length;

	name_length = ft_strlen(name) + 1;
	new_length = ft_strlen(str) - (name_length) + ft_strlen(value);
	new_str = malloc(sizeof(char) * new_length + 1);
	if (!new_str)
		return (NULL);
	printf("namelen=%d, newlen=%d, env_pos=%d\n", name_length, new_length, env_pos);
	strncpy(new_str, str, env_pos);
	new_str[env_pos] = '\0';
	printf("newstr1=%s\n", new_str);
	strcat(new_str, value);
	printf("newstr2=%s\n", new_str);
	strcat(new_str, str + env_pos + (name_length));
	printf("newstr3=%s\n", new_str);
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