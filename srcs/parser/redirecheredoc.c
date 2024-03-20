/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecheredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:33:04 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/20 21:21:11 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		ft_hd_parent(file, fd, cmd, state);
}

void	ft_hd_child(char *str, int fd, t_state *state)
{
	char	*buffer;

	ft_signals(EXEC);
	while (1)
	{
		write(1, "> ", 2);
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer)
		{
			write(1, "\n", 1);
			break ;
		}
		if (!ft_strcmp_ignore_nl(str, buffer))
			break ;
		expnvar(&buffer, 0, ft_strlen(buffer), state);
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	close(fd);
	exit(0);
}

void	ft_hd_parent(char *file, int fd, t_command *cmd, t_state *state)
{
	int	status;

	waitpid(-1, &status, 0);
	if (WIFSIGNALED(status))
	{
		close(fd);
		state->data->exit_status = WTERMSIG(status) + 128;
		state->to_stop = true;
	}
	else
		open_fd(&cmd->fd_in, file, O_RDONLY, state);
	free(file);
}
