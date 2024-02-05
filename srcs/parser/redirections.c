/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:33:53 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/05 15:36:14 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_parse_tokens(t_state *state)
{
	t_command	*command;

	command = state->cmd_list;
	while (command)
	{
		handle_redirections(command, state);
		handle_heredoc(command, state);
		command = command->next;
	}
}

void	handle_heredoc(t_command *cmd, t_state *state)
{
	
}

void	handle_redirections(t_command *cmd, t_state *state)
{
	t_token	*current;
	t_token	*file_token;
	t_token *next_token;

	current = cmd->tokens;
	while (current)
	{
		if (current->type == INPUT || current->type == OUTPUT \
		|| current->type == APPEND)
		{
			next_token = current->next;
			file_token = next_token;
			if (!file_token || file_token->type != WORD)
				ft_exit("Missing file after redirection\n", state);
			if (current->type == INPUT)
				cmd->fd_in = open(file_token->str, O_RDONLY);
			else if (current->type == OUTPUT)
				cmd->fd_out = open(file_token->str, \
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (current->type == APPEND)
				cmd->fd_out = open(file_token->str, \
				O_WRONLY | O_CREAT | O_APPEND, 0644);
			next_token = file_token->next;
			remove_token(&cmd->tokens, current);
			remove_token(&cmd->tokens, file_token);
			current = next_token;
		}
		else
			current = current->next;
	}
}
