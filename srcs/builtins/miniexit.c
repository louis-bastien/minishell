/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniexit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:10:31 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/07 10:11:10 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mini_exit(char **cmd)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	if (cmd[1] && cmd[2])
	{
		ft_putstr_fd("Minishell: exit: to many argumnets\n", 2);
		return (1);
	}
	//necesito determinar el exit estatus de la estructura
	//antes de salir debe liberar memoria
	return (0);
}
