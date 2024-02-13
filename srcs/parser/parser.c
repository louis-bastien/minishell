/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:23:00 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/13 13:03:34 by agheredi         ###   ########.fr       */
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

	token_counter = count_upto_pipe(tokens);
	if (token_counter)
	{
		if (add_cmd(&state->cmd_list, tokens, token_counter))
			ft_error("(parser) Failed to add new cmd", state);
		else
		{
			while (tokens && tokens->type != PIPE)
				tokens = tokens->next;
			if (tokens)
				init_cmd_list(tokens->next, state);
		}
	}
	else
		ft_error("Use pipes with valid commands", state);
}

int	add_cmd(t_command **cmd_list, t_token *tokens, int token_counter)
{
	t_command	*new_cmd;
	t_command	*tmp;

	tmp = *cmd_list;
	new_cmd = create_cmd(tokens, token_counter);
	if (!new_cmd)
		return (1);
	if (!tmp)
		*cmd_list = new_cmd;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
	}
	return (0);
}

t_command	*create_cmd(t_token *tokens, int token_counter)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->command = NULL;
	new_cmd->args = NULL;
	new_cmd->args_count = 0;
	new_cmd->tokens = import_tokens(tokens, token_counter);
	parse_type(new_cmd->tokens);
	new_cmd->fd_in = -1;
	new_cmd->fd_out = 1;
	new_cmd->next = NULL;
	return (new_cmd);
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
