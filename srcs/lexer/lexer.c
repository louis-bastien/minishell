/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:50:48 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/04 16:07:48 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lexer(char *input, t_state *state)
{
	t_token	*token_list;

	token_list = NULL;
	create_tokens(&token_list, input, state);
	state->token_list = token_list;
}

void	create_tokens(t_token **token_list, char *input, t_state *state)
{
	char	*token_str;
	char	*reader;
	t_ttype type;

	token_str = NULL;
	reader = input;
	while (*reader)
	{
		skip_whitespaces(&reader);
		if (!*reader)
			break ;
		token_str = generate_token(&reader, state);
		type = parse_type(token_str);
		if (!token_str)
		{
			ft_error("Failed to parse token content", state);
			break ;
		}
		else
		{
			if (add_token(token_list, token_str, type))
				ft_error("Failed to add/malloc token", state);
		}
	}
}

char	*generate_token(char **reader, t_state *state)
{
	char	*token_str;

	token_str = NULL;
	if (is_single_token(*reader) || is_double_token(*reader))
		token_str = handle_token(reader, state);
	else if (is_validchar(**reader))
		token_str = handle_string(reader, state);
	else
	{
		ft_error("Unrecognized character in input", state);
		return (NULL);
	}
	return (token_str);
}

t_ttype	parse_type(char *token)
{
	char	*str;

	str = token;
	if (*str == '|')
		return (PIPE);
	else if (*str == '<')
	{
		if (str[1])
			return (HEREDOC);
		else
			return (INPUT);
	}
	else if (*str == '>')
	{
		if (str[1])
			return (APPEND);
		else
			return (OUTPUT);
	}
	else
		return (WORD);
}

int	is_validchar(char c)
{
	if (c == '\0')
		return (0);
	if (is_token(c))
		return (0);
	else if (is_whitespace(c))
		return (0);
	else if (ft_isprint(c))
		return (1);
	else
		return (0);
}
