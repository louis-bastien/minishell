/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:58:13 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/22 22:00:52 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_parse_path(char **envp)
{
	char	*str_path;
	char	**all_path;

	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			str_path = ft_strdup(*envp + 5);
		envp++;
	}
	all_path = ft_split(str_path, ':');
	free(str_path);
	return (all_path);
}

char	*get_path(t_command *cmd, t_state *state)
{
	char	**all_path;
	int		i;
	char	*exec;
	char	*path_part;

	i = 0;
	if (check_absolute_path(cmd))
		return (cmd->command);
	all_path = ft_parse_path(state->data->env);
	if (all_path == NULL || cmd == NULL)
		ft_error_exec(cmd->command, -1, "Error Parsing Path", state);
	while (all_path[i] != NULL)
	{
		path_part = ft_strjoin(all_path[i], "/");
		exec = ft_strjoin(path_part, cmd->command);
		free(path_part);
		if (access(exec, F_OK) == 0)
			return (exec);
		free(exec);
		i++;
	}
	ft_error_exec(cmd->command, NOCMD, "Command does not exist", state);
	return (NULL);
}

int	check_absolute_path(t_command *cmd)
{
	char	*last_slash;
	char	*relative_cmd;

	if (is_absolute(cmd))
	{
		last_slash = ft_strrchr(cmd->command, '/');
		relative_cmd = last_slash + 1;
		if (cmd->args[0])
			free(cmd->args[0]);
		cmd->args[0] = ft_strdup(relative_cmd);
		return (1);
	}
	return (0);
}

int	is_absolute(t_command *cmd)
{

	if (cmd->command[0] == '/')
		return (1);
	else if (cmd->command[0] == '.' && cmd->command[1] == '/')
		return (1);
	else
		return (0);
}
