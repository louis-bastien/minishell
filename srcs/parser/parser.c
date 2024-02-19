/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:23:00 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/19 17:22:30 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_parser(t_state *state)
{
	init_cmd_list(state->token_list, state);
	if (!state->error)
		ft_parse_tokens(state);
}

void	init_cmd_list(t_token *tokens, t_state *state)
{
	int		token_counter;
	int		cmd_counter;

	token_counter = count_upto_pipe(tokens);
	cmd_counter = 0;
	if (token_counter != 0)
	{
		cmd_counter++;
		if (add_cmd(&state->cmd_list, tokens, token_counter, cmd_counter))
			ft_error("(parser) Failed to add new cmd", state);
		else
		{
			state->num_cmds++;
			while (tokens && tokens->type != PIPE)
				tokens = tokens->next;
			if (tokens)
				init_cmd_list(tokens->next, state);
		}
	}
	else
		ft_error("Use pipes between commands", state);
}

int	count_upto_pipe(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != PIPE)
	{
		count++;
		tokens = tokens ->next;
	}
	return (count);
}
