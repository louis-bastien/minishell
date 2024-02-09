/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:28:05 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/09 20:47:27 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	one_cmd(t_state *state)
{
	if (state->cmd_list->is_builtin == 0)
		ft_builtins(state);
	else
	{
		//crear un hijo para ejecutar el cmd
	}
	return (0);
}

int	pre_executor(t_state *state)
{
	if (state->data->pipes == 0)
		one_cmd(state);
	else
	{
		//malloc de los pid
		//executor
	}
	return (0);
}
