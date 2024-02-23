/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:05:46 by agusheredia       #+#    #+#             */
/*   Updated: 2024/02/23 20:49:22 by agusheredia      ###   ########.fr       */
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
	if (cmd->command[0] == '/')
	{
		path = ft_strdup(cmd->command);
		printf("%s\n", path);
		tmp = ft_split(cmd->command, '/');
		i = ft_sizesplit(tmp);
		cmd->args[0] = ft_strdup(tmp[i - 1]);
		cmd->args[1] = NULL;
	}
	else
		path = get_path(cmd, state, env);
	execve(path, cmd->args, env);
	free(path);
	free_darray(tmp);
	ft_error_exec(cmd->command, EXIT_FAILURE, "Execution Failed", state);
	exit(EXIT_FAILURE);
}
