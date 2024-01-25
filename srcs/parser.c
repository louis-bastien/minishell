/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:23:00 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/25 16:40:59 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parser(t_state *state)
{
	t_item		*tokens;

	ft_init_cmds(state->item_list, state);
}

void	ft_init_cmds(t_item *tokens, t_state *state)
{
	int		item_counter;

	item_counter = count_upto_pipe(tokens);
	if (add_cmd(&state->cmds, tokens, item_counter))
		ft_exit("(parser) Failed to add new cmd", state);
	while (tokens && tokens->token != PIPE)
		tokens = tokens->next;
	if (tokens)
		ft_init_cmds(tokens->next, state);
}

int	add_cmd(t_command **cmds, t_item *tokens, int item_counter)
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

t_command	*create_cmd(t_item *tokens, int item_counter)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->items = import_items(tokens, item_counter);
	new_cmd->command = NULL;
	new_cmd->args = NULL;
	new_cmd->infile = NULL;
	new_cmd->outfile = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

int	count_upto_pipe(t_item *tokens)
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
