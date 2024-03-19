/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:50:25 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/19 12:05:51 by agheredi         ###   ########.fr       */
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

char	*ft_join_path(char *strpath, t_command *cmd)
{
	char	*path_part;
	char	*exec;

	path_part = ft_strjoin(strpath, "/");
	exec = ft_strjoin(path_part, cmd->command);
	free(path_part);
	return (NULL);
}

char	*get_path(t_command *cmd, t_state *state, char **env)
{
	char	**all_path;
	int		i;
	char	*exec;

	i = 0;
	if (!get_var_env("PATH", env))
	{
		ft_error_perm(NOCMD, cmd->command);
		return (NULL);
	}
	all_path = ft_parse_path(env);
	if (all_path == NULL || cmd == NULL)
		ft_error_exec(cmd->command, -1, "Error Parsing Path", state);
	while (all_path[i++] != NULL)
	{
		exec = ft_join_path(all_path[i], cmd);
		if (access(exec, F_OK) == 0)
			return (exec);
		free(exec);
		i++;
	}
	if (!cmd->is_builtin)
		exit_error(NOCMD, cmd->command, state);
	return (NULL);
}
