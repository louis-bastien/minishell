/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:33:53 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/11 17:20:51 by lbastien         ###   ########.fr       */
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
	{
		handle_heredoc(file_token, cmd, state);
		ft_signals(NON_EXEC);
	}
}

void	handle_heredoc(t_token *token, t_command *cmd, t_state *state)
{
	int		fd;
	char	*file;
	int		pid;
	char	*numhd;

	ft_signals(STOP);
	fd = -1;
	state->heredoc++;
	numhd = ft_itoa(state->heredoc);
	file = ft_strjoin(".heredoc", numhd);
	free(numhd);
	if (cmd->fd_in > 1)
		close(cmd->fd_in);
	open_fd(&fd, file, O_WRONLY | O_CREAT | O_TRUNC, state);
	pid = fork();
	if (pid < 0)
		ft_error_exec(cmd->command, -1, "Error forking heredoc process", state);
	else if (pid == 0)
		ft_hd_child(token->str, fd, state);
	else
		ft_hd_parent(file, cmd, state);
}

void	ft_hd_child(char *str, int fd, t_state *state)
{
	char	*buffer;

	ft_signals(EXEC);
	while (!g_signal_received)
	{
		write(1, "> ", 2);
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer)
		{
			printf("Heredoc no buffer\n");
			break ;
		}
		if (!ft_strcmp(str, buffer))
			break ;
		expnvar(&buffer, 0, ft_strlen(buffer), state);
		write(fd, buffer, ft_strlen(buffer));
		printf("buffer=%s\n", buffer);
		free(buffer);
	}
	free(buffer);
	close(fd);
	exit(0);
}

void	ft_hd_parent(char *file, t_command *cmd, t_state *state)
{
	int	status;

	waitpid(-1, &status, 0);
	open_fd(&cmd->fd_in, file, O_RDONLY, state);
	free(file);
}

void	open_fd(int *fd, const char *file, int flags, t_state *state)
{
	if (*fd > 1)
		close(*fd);
	*fd = open(file, flags, 0644);
	if (*fd < 0)
		ft_error("(parser) could not open tmp file for heredoc", state);
}
