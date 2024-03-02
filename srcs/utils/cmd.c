/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:31:33 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/02 18:08:46 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_first(t_command *cmd)
{
	if (cmd->index == 1)
		return (1);
	else
		return (0);
}

int	is_last(t_command *cmd, t_state *state)
{
	if (cmd->index == state->num_cmds)
		return (1);
	else
		return (0);
}
