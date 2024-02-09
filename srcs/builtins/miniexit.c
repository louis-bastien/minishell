/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniexit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:10:31 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/09 20:45:55 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mini_exit(t_state *state)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	if (state->cmd_list->args[1] && state->cmd_list->args[2])
	{
		ft_putstr_fd("Minishell: exit: to many argumnets\n", 2);
		return (1);
	}
	//necesito determinar el exit estatus de la estructura
	//antes de salir debe liberar memoria
	return (0);
}
