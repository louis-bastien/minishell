/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:23:00 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/26 15:36:49 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parser(t_state *state)
{
	t_token		*tokens;

	ft_init_cmds(state->token_list, state);
	ft_handle_redirects(state);
}

void	init_cmds(t_token *tokens, t_state *state)
{
	int		item_counter;

	item_counter = count_upto_pipe(tokens);
	if (add_cmd(&state->cmds, tokens, item_counter))
		ft_exit("(parser) Failed to add new cmd", state);
	while (tokens && tokens->token != PIPE)
		tokens = tokens->next;
	if (tokens)
		init_cmds(tokens->next, state);
}

int	add_cmd(t_command **cmds, t_token *tokens, int item_counter)
{
	t_command	*new_cmd;
	t_command	*tmp;

	tmp = *cmds;
	new_cmd = create_cmd(tokens, item_counter);
	if (!new_cmd)
		return (1);
	if (!tmp)
		*cmds = new_cmd;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
	}
	return (0);
}

t_command	*create_cmd(t_token *tokens, int item_counter)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->tokens = import_tokens(tokens, item_counter);
	new_cmd->command = NULL;
	new_cmd->args = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

int	count_upto_pipe(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->token != PIPE)
	{
		count++;
		tokens = tokens ->next;
	}
	return (count);
}
