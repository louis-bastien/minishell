/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:50:25 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/16 15:36:39 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**copy_env(char **env, t_state *state)
{
	char	**data_env;
	int		i;
	int		size_env;

	i = 0;
	size_env = double_array_size(env);
	data_env = (char **)malloc(sizeof(char *) * (size_env + 1));
	if (!data_env)
		ft_exit("Failed to malloc data_env", state);
	i = 0;
	while (i < size_env)
	{
		data_env[i] = ft_strdup(env[i]);
		i++;
	}
	data_env[i] = NULL;
	return (data_env);
}

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

char	*get_path(char **all_path, char *cmd)
{
	int		i;
	char	*exec;
	char	*path_part;

	if (all_path == NULL || cmd == NULL)
		return (NULL);
	i = 0;
	while (all_path[i] != NULL)
	{
		path_part = ft_strjoin(all_path[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(exec, F_OK) == 0)
			return (exec);
		free(exec);
		i++;
	}
	return (NULL);
}

void	is_builtins(t_state *state)
{
	if (!ft_strncmp(state->cmd_list->command, "cd", 3))
		state->cmd_list->is_builtin = 0;
	else if (!ft_strncmp(state->cmd_list->command, "pwd", 4))
		state->cmd_list->is_builtin = 0;
	else if (!ft_strncmp(state->cmd_list->command, "echo", 5))
		state->cmd_list->is_builtin = 0;
	else if (!ft_strncmp(state->cmd_list->command, "export", 7))
		state->cmd_list->is_builtin = 0;
	else if (!ft_strncmp(state->cmd_list->command, "unset", 6))
		state->cmd_list->is_builtin = 0;
	else if (!ft_strncmp(state->cmd_list->command, "env", 4))
		state->cmd_list->is_builtin = 0;
	else if (!ft_strncmp(state->cmd_list->command, "exit", 5))
		state->cmd_list->is_builtin = 0;
	else
		state->cmd_list->is_builtin = 1;
}
