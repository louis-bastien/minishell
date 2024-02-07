/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniecho.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:08:26 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/07 10:08:53 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mini_echo(int outfd, char **cmd)
{
	int	i;
	int	flag;

	i = 2;
	flag = 0;
	if (cmd && cmd[i][0] == '-' && cmd[i][1] == 'n')
	{
		flag = 1;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], outfd);
		i++;
		if (cmd[i])
			ft_putstr_fd(" ", outfd);
	}
	if (flag == 0)
		ft_putstr_fd("\n", outfd);
	return (0);
}
