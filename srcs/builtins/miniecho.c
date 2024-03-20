/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniecho.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:08:26 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/20 21:31:26 by lbastien         ###   ########.fr       */
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

int	is_flag(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
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
	while (cmd->args[i] && is_flag(cmd->args[i]))
	{
		flag = 1;
		i++;
	}
	print_argecho(cmd->args, i, fd_out);
	if (flag == 0)
		ft_putstr_fd("\n", fd_out);
	return (0);
}
