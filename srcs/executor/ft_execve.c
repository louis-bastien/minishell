/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:05:46 by agusheredia       #+#    #+#             */
/*   Updated: 2024/03/16 20:28:38 by agusheredia      ###   ########.fr       */
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

void	ft_execve(t_command *cmd, char *path, t_state *state, char **env)
{
	execve(path, cmd->args, env);
	free(path);
	ft_error_exec(cmd->command, EXIT_FAILURE, "Execution Failed", state);
	exit(EXIT_FAILURE);
}

int	is_absolute(t_command *cmd)
{
	if (ft_strnstr(&cmd->command[0], "bin", 3))
	{
		if (cmd->command[0] == '/')
			return (1);
		else if (cmd->command[0] == '.' && cmd->command[1] == '/')
			return (1);
	}
	else if (!ft_strnstr(&cmd->command[0], "bin", 3))
		return (-1);
	return (0);
}
