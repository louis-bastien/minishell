/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:33:53 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/05 14:29:56 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_parse_tokens(t_state *state)
{
	t_command	*command;

	command = state->cmd_list;
	while (command)
	{
		if (!state->error)
			handle_redirections(command, state);
		if (!state->error)
			handle_command(command, state);
		if (!state->error)
			handle_args(command, state);
		if (!state->error)
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
				ft_error("Missing file after redirection", state);
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
		handle_heredoc(file_token, cmd, state);
}

void	handle_heredoc(t_token *token, t_command *cmd, t_state *state)
{
	int		fd;
	char	*buffer;

	if (cmd->fd_in > 1)
		close(cmd->fd_in);
	fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		ft_error("(parser) could not open tmp file for heredoc", state);
	while (1)
	{
		write(1, "> ", 2);
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer)
			ft_error("(parser) empty buffer for heredoc", state);
		if (!ft_strncmp(token->str, buffer, ft_strlen(buffer) - 1))
			break ;
		expnvar(&buffer, 0, ft_strlen(buffer), state);
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
	cmd->fd_in = fd;
	free(buffer);
}

void	open_fd(int *fd, const char *filename, int flags, t_state *state)
{
	if (*fd > 1)
		close(*fd);
	*fd = open(filename, flags, 0644);
	if (*fd < 0)
		ft_error("(parser) could not open tmp file for heredoc", state);
}


