/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:35:13 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/30 18:44:11 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_cmds(t_command *commands)
{
	int	index;

	index = 0;
	while (commands)
	{
		printf("==Command %d:\n", index);
		print_token(commands->tokens);
		printf("==\n");
		index++;
		commands = commands->next;
	}
}