/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:18:17 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/08 20:07:16 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_expander(t_state *state)
{
	t_token	*token;

	token = state->token_list;
	while (token)
	{
		quote_wrapper(&token->str, state);
		token = token->next;
	}
}

void	quote_wrapper(char **str, t_state *state)
{
	char	*current;

	current = *str;
	while (*current)
	{
		printf("char=%c\n", *current);
		if (*current == '\'')
			parse_single_quotes(str, &current, state);
		// else if (*current == '\"')
		// 	parse_double_quotes(str, &current, state);
		// else
		// 	parse_unquoted(str, &current, state);
		current++;
	}
}

void	parse_single_quotes(char **str, char **current, t_state *state)
{
	char	*end;

	end = ft_strchr(*current + 1, '\'');
	if (!end)
		ft_error("Unclosed quote", state);
	printf("endpos=%ld, startpos=%ld\n", end - *str, *current - *str);
	remove_char_from_string(*str, end - *str);
	remove_char_from_string(*str, *current - *str);
}

void	remove_char_from_string(char *str, int pos)
{
	int	len;

	len = ft_strlen(str);
	if (pos > 0 && pos < len)
		ft_memmove(str + pos, str + pos + 1, len - pos);
}

// char *get_closing_quote(char *str)
// {
// 	char	opening_quote;
// 	char	closing_quote;
// 	char	quote_ptr;

// 	opening_quote = *str;
// 	while (str++)
// 	{
// 		if (is_quote(*str))
// 		{
// 			closing_quote = *str;
// 			quote_ptr = str;
// 		}
// 	}
// 	if (opening_quote == closing_quote)
// 		return (quote_ptr);
// 	else
// 		return (NULL);
// }

// char	*expand_env_variables(char *str, t_state *state)
// {
// 	char	*new_str;
// 	char	*value;
// 	int		env_pos;
// 	char	*current;

// 	current = *str;
// 	while (*current)
// 	{
// 		if (*current == '$' && is_valid_env(*(current + 1)))
// 		{
// 			env_pos = current - str;
// 			value = get_env_value(current, state);
// 			new_str = replace_env(str, env_pos, value);
// 			if (!new_str)
// 				ft_error("Failed to generate expanded string", state);
// 			free(str);
// 			str = new_str;
// 			current = new_str + env_pos + ft_strlen(value);
// 		}
// 		else
// 			current++;
// 	}
// 	return (str);
// }

char	*replace_env(char *str, int env_pos, char *value)
{
	char	*new_str;
	int		new_length;
	int		name_length;

	name_length = ft_strlen(get_env_name(str + env_pos)) + 1;
	new_length = ft_strlen(str) - (name_length) + ft_strlen(value);
	new_str = malloc(sizeof(char) * new_length + 1);
	if (!new_str)
		return (NULL);
	strncpy(new_str, str, env_pos);
	new_str[env_pos] = '\0';
	strcat(new_str, value);
	strcat(new_str, str + env_pos + (name_length));
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

// char	*handle_quotes(char **reader, t_state *state)
// {
// 	char	*token_str;
// 	char	quote;
// 	int		i;

// 	quote = *(*reader)++;
// 	token_str = NULL;
// 	i = 0;
// 	while ((*reader)[i] && (*reader)[i] != quote)
// 		i++;
// 	if ((*reader)[i] != quote)
// 		ft_error("Unclosed quote", state);
// 	else
// 	{
// 		token_str = ft_strndup(*reader, i);
// 		if (!token_str && i)
// 			ft_error("Failed to malloc quoted token", state);
// 		(*reader)++;
// 	}
// 	return (token_str);
// }
