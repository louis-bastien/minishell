/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniecho.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:08:26 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/09 20:37:39 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mini_echo(t_state *state)
{
	int	i;
	int	flag;

	i = 2;
	flag = 0;
	if (state->cmd_list->args && state->cmd_list->args[i][0] == '-'
		&& state->cmd_list->args[i][1] == 'n')
	{
		flag = 1;
		i++;
	}
	while (state->cmd_list->args[i])
	{
		ft_putstr_fd(state->cmd_list->args[i], state->cmd_list->fd_out);
		i++;
		if (state->cmd_list->args[i])
			ft_putstr_fd(" ", state->cmd_list->fd_out);
	}
	if (flag == 0)
		ft_putstr_fd("\n", state->cmd_list->fd_out);
	return (0);
}
