/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor(pipex).c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:56:13 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/20 17:04:53 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/minishell.h"

// void	close_pipes(t_state *state)
// {
// 	int	i;

// 	i = 0;
// 	while (i < state->data->nun_pipes)
// 	{
// 		close(state->data->pipe[i][0]);
// 		close(state->data->pipe[i][1]);
// 		i++;
// 	}
// }

// static void	sub_dup2(int zero, int first)
// {
// 	dup2(zero, 0);
// 	dup2(first, 1);
// }

// void	child(t_state *state)
// {
// 	char	*path;
// 	char	**cmd;
// 	char	**all_path;
// 	int		idx;

// 	idx = state->data->idx;
// 	state->data->pid = fork();
// 	if (!state->data->pid)
// 	{
// 		if (state->data->idx == 0)
// 			sub_dup2(state->cmd_list->fd_in, state->data->pipe[idx][1]);
// 		else if (state->data->idx == (state->data->nun_pipes))
// 			sub_dup2(state->data->pipe[idx - 1][0], state->cmd_list->fd_out);
// 		else
// 			sub_dup2(state->data->pipe[idx -1][0], state->data->pipe[idx][1]);
// 		close_pipes(state);
// 		cmd = ft_split(p->cmd[p->idx], ' ');
// 		all_path = ft_parse_path(state->data->env);
// 		path = get_path(all_path, cmd);
// 		if (path == NULL)
// 			ft_error(NOCMD, cmd[0]);
// 		execve(path, cmd, state->data->env);
// 		free(path);
// 		free(cmd);
// 	}
// }

// void	multiple_cmd(t_state *state)
// {
// 	int	status;
// 	int	i;

// 	i = -1;
// 	while (++i < state->data->nun_pipes)
// 	{
// 		state->data->pipe[i] = malloc(sizeof(int) * 2);
// 		if (!state->data->pipe[i])
// 			ft_error_perm(42, "Malloc\n");
// 		pipe(state->data->pipe[i]);
// 	}
// 	state->data->idx = -1;
// 	while (++state->data->idx < state->data->nun_pipes + 1)
// 		child(state);
// 	close_pipes(state);
// 	waitpid(-1, &status, 0);
// }
