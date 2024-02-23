/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:31:33 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/20 13:36:45 by lbastien         ###   ########.fr       */
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