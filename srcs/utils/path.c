/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:50:25 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/23 19:16:50 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**copy_env(char **env)
{
	char	**data_env;
	int		i;
	int		size_env;

	i = 0;
	size_env = double_array_size(env);
	data_env = (char **)malloc(sizeof(char *) * (size_env + 1));
	if (!data_env)
		return (NULL);
	while (i < size_env && env[i] != NULL)
	{
		data_env[i] = ft_strdup(env[i]);
		if (!data_env[i])
		{
			free_darray(data_env);
			return (NULL);
		}
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

char	*get_path(t_command *cmd, t_state *state, char **env)
{
	if (get_var_index("PATH", env) != -1)
	{
		state->data->all_path = ft_parse_path(env);
		if (state->data->all_path == NULL || cmd == NULL)
			ft_error_exec(cmd->command, -1, "Error Parsing Path", state);
		return (find_executable(cmd, state));
	}
	exit_error(NOCMD, cmd->command, state);
	return (NULL);
}

char	*find_executable(t_command *cmd, t_state *state)
{
	char	*exec;
	char	*path_part;
	int		i;

	i = 0;
	while (state->data->all_path[i] != NULL)
	{
		path_part = ft_strjoin(state->data->all_path[i], "/");
		exec = ft_strjoin(path_part, cmd->command);
		free(path_part);
		if (access(exec, F_OK) == 0)
		{
			free_doubleptr(state->data->all_path);
			state->data->all_path = NULL;
			return (exec);
		}
		free(exec);
		i++;
	}
	free_doubleptr(state->data->all_path);
	state->data->all_path = NULL;
	exit_error(NOCMD, cmd->command, state);
	return (NULL);
}

int	path_valid(char *path)
{
	struct stat	file_stat;
	int			num;

	num = stat(path, &file_stat);
	if (num == -1)
		return (0);
	else
		return (1);
}
