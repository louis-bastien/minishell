/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_absolute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:46:24 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/25 12:46:45 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_absolute(t_command *cmd)
{
	if (cmd->command[0] == '/' || \
		(cmd->command[0] == '.' && cmd->command[1] == '/'))
	{
		if (path_valid(cmd->command))
			return (1);
	}
	return (0);
}
