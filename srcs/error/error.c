/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:04:09 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/15 15:11:52 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error_sms(char *str)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(str, 2);
}

void	ft_error_perm(int perm, char *str)
{
	if (perm == NOREAD || perm == NOWRITE)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (perm == 404)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (perm == NOCMD)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(": command not found: ", 2);
		ft_putendl_fd(str, 2);
	}
	else if (perm == 42)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(str, 2);
	}
}
