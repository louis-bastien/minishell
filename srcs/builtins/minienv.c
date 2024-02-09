/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minienv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:10:07 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/09 20:44:43 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mini_env(t_state *state)
{
	int	i;

	i = 0;
	while (state->data->env[i])
	{
		ft_putendl_fd(state->data->env[i], state->cmd_list->fd_out);
		i++;
	}
	return (0);
}
