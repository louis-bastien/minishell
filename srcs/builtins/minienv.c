/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minienv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:10:07 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/23 20:22:11 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mini_env(t_command *cmd, char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		ft_putendl_fd((*env)[i], cmd->fd_out);
		i++;
	}
	return (0);
}
