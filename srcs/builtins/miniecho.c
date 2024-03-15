/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniecho.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:08:26 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/15 15:22:22 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_argecho(char **args, int i, int fd_out)
{
	while (args[i])
	{
		ft_putstr_fd(args[i], fd_out);
		i++;
		if (args[i])
			ft_putstr_fd(" ", fd_out);
	}
}

int	mini_echo(t_command *cmd, int fd_out)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!cmd->args[1])
	{
		ft_putstr_fd("\n", fd_out);
		return (0);
	}
	if (cmd->args[i][0] == '-' && cmd->args[i][1] == 'n')
		flag = 1;
	while (cmd->args[i] && cmd->args[i][0] == '-'
		&& cmd->args[i][1] == 'n')
		i++;
	print_argecho(cmd->args, i, fd_out);
	if (flag == 0)
		ft_putstr_fd("\n", fd_out);
	return (0);
}
