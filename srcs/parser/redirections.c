/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:33:53 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/02 14:09:18 by lbastien         ###   ########.fr       */
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
//		handle_heredoc(command, state);
		command = command->next;
	}
}

void	handle_redirections(t_command *cmd, t_state *state)
{
	t_token	*current;
	t_token	*file_token;

	current = cmd->tokens;
	while (current)
	{
		if (current->type == INPUT || current->type == OUTPUT \
		|| current->type == APPEND)
		{
			file_token = current->next;
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
			current = file_token->next;
		}
		else
			current = current->next;
	}
}

// void	remove_token(t_token **token_list, t_token *token)
// {
// 	if (token->prev)
// 		token->prev->next = token->next;
// 	else
// 		*token_list = token->next;
// 	free_token(token);
// }
