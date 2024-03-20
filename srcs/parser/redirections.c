/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:33:53 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/20 13:36:27 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_parse_tokens(t_state *state)
{
	t_command	*command;

	command = state->cmd_list;
	while (command)
	{
		if (to_continue(state))
			handle_redirections(command, state);
		if (to_continue(state))
			handle_command(command, state);
		if (to_continue(state))
			handle_args(command, state);
		if (to_continue(state))
			check_builtins(command);
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
		|| current->type == APPEND || current->type == HEREDOC)
		{
			file_token = current->next;
			if (!file_token || file_token->type != WORD)
			{
				ft_error("syntax error near unexpected token `newline'", state);
				state->data->exit_status = 2;
				break ;
			}
			else
				parse_fd(current, cmd, state);
			remove_token(&cmd->tokens, current);
			current = file_token->next;
			remove_token(&cmd->tokens, file_token);
		}
		else
			current = current->next;
	}
}

void	parse_fd(t_token *token, t_command *cmd, t_state *state)
{
	t_token	*file_token;

	file_token = token->next;
	if (token->type == INPUT)
		open_fd(&cmd->fd_in, file_token->str, O_RDONLY, state);
	else if (token->type == OUTPUT)
		open_fd(&cmd->fd_out, file_token->str, \
		O_WRONLY | O_CREAT | O_TRUNC, state);
	else if (token->type == APPEND)
		open_fd(&cmd->fd_out, file_token->str, \
		O_WRONLY | O_CREAT | O_APPEND, state);
	else if (token->type == HEREDOC)
	{
		handle_heredoc(file_token, cmd, state);
		ft_signals(NON_EXEC);
	}
}

void	open_fd(int *fd, const char *file, int flags, t_state *state)
{
	struct stat	file_stat;

	if (*fd > 1)
		close(*fd);
	*fd = open(file, flags, 0644);
	if (*fd < 0)
	{
		state->to_stop = false;
		if (stat(file, &file_stat) == 0 && S_ISDIR(file_stat.st_mode))
		{
			state->data->exit_status = 1;
			ft_error_open(55, (char *)file);
		}
		else if (errno == EACCES)
		{
			state->data->exit_status = 1;
			ft_error_open(1, (char *)file);
		}
		else
		{
			state->data->exit_status = 1;
			ft_error_open(404, (char *)file);
		}
	}
}
