/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:00:00 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/25 17:01:43 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd(t_command *cmd)
{
	if (cmd)
	{
		if (cmd->command)
			free(cmd->command);
		if (cmd->args)
			free_args(cmd);
		if (cmd->items)
			free_items(cmd->items);
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		free(cmd);
		cmd = NULL;
	}
}

void	free_node(t_item *node)
{
	if (node)
	{
		if (node->str)
			free(node->str);
		free(node);
		node = NULL;
	}
}

void	free_args(t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->args_count)
		free(cmd->args[i++]);
	free(cmd->args);
}
