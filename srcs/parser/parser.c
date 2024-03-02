/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:23:00 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/02 18:17:53 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_parser(t_state *state)
{
	//printf("entra ft_parser\n");
	init_cmd_list(state->token_list, state);
	if (!state->error)
		ft_parse_tokens(state);
}

void	init_cmd_list(t_token *tokens, t_state *state)
{
	int		token_counter;

	token_counter = count_upto_pipe(tokens);
	if (token_counter != 0)
	{
		state->num_cmds++;
		if (add_cmd(&state->cmd_list, tokens, token_counter, state->num_cmds))
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
		ft_error("Use pipes between commands", state);
}

int	add_cmd(t_command **cmd_list, t_token *tokens, int numtok, int numcmd)
{
	t_command	*new_cmd;
	t_command	*tmp;

	tmp = *cmd_list;
	new_cmd = create_cmd(tokens, numtok, numcmd);
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

t_command	*create_cmd(t_token *tokens, int numtok, int numcmd)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->command = NULL;
	new_cmd->args = NULL;
	new_cmd->index = numcmd;
	new_cmd->args_count = 0;
	new_cmd->tokens = import_tokens(tokens, numtok);
	parse_type(new_cmd->tokens);
	new_cmd->fd_in = STDIN_FILENO;
	new_cmd->fd_out = STDOUT_FILENO;
	new_cmd->is_builtin = false;
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
