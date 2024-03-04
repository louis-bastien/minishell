/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minienv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:10:07 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/04 16:41:47 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mini_env(t_command *cmd, char ***env)
{
	int	i;

	(void)cmd;
	i = 0;
	while ((*env)[i])
	{
		ft_putendl_fd((*env)[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
