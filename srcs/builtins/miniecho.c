/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniecho.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:08:26 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/06 10:19:24 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_argecho(char **args, int i)
{
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		i++;
		if (args[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
}

int	mini_echo(t_command *cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!cmd->args[i])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	while (cmd->args && cmd->args[i][0] == '-'
		&& cmd->args[i][1] == 'n')
	{
		flag = 1;
		i++;
	}
	print_argecho(cmd->args, i);
	if (flag == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
