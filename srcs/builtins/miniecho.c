/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniecho.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:08:26 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/23 21:05:52 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mini_echo(t_command *cmd)
{
	int	i;

	i = 1;
	if (!cmd->args[i])
	{
		ft_putstr_fd("\n", cmd->fd_out);
		return (0);
	}
	if (cmd->args && cmd->args[i][0] == '-'
		&& cmd->args[i][1] == 'n')
	{
		i++;
		while (cmd->args[i])
		{
			ft_putstr_fd(cmd->args[i], cmd->fd_out);
			i++;
			if (cmd->args[i])
				ft_putstr_fd(" ", cmd->fd_out);
		}
	}
	if (!cmd->args[i] || cmd->args[i][0] != '-')
		ft_putstr_fd("\n", cmd->fd_out);
	return (0);
}
