/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:05:46 by agusheredia       #+#    #+#             */
/*   Updated: 2024/03/11 14:10:38 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_sizesplit(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	ft_execve(t_command *cmd, t_state *state, char **env)
{
	char	*path;
	char	*tmp;

	tmp = NULL;
	if (is_absolute(cmd))
	{
		path = ft_strdup(cmd->command);
		tmp = ft_strrchr(cmd->command, '/');
		cmd->args[0] = ft_strdup(tmp);
	}
	else
		path = get_path(cmd, state, env);
	execve(path, cmd->args, env);
	free(path);
	ft_error_exec(cmd->command, EXIT_FAILURE, "Execution Failed", state);
	exit(EXIT_FAILURE);
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
