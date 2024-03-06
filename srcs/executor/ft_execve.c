/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:05:46 by agusheredia       #+#    #+#             */
/*   Updated: 2024/03/06 11:10:47 by agheredi         ###   ########.fr       */
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
	char	**tmp;
	int		i;

	tmp = NULL;
	if (is_absolute(cmd))
	{
		path = ft_strdup(cmd->command);
		tmp = ft_split(cmd->command, '/');
		i = ft_sizesplit(tmp);
		cmd->args[0] = ft_strdup(tmp[i - 1]);
		cmd->args[1] = NULL;
	}
	else
		path = get_path(cmd, state, env);
	free_darray(tmp);
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
