/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:20:02 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/14 17:53:38 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error_builtin(int perm, char *cmd, char *arg)
{
	if (perm == 55)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": invalid option\n", 2);
	}
	else if (perm == 1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else if (perm == 404)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

void	ft_error_exit(int perm, char *arg)
{
	if (perm == 55)
	{
		ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else if (perm == 1)
	{
		ft_putstr_fd("Minishell: exit:", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": too many arguments\n", 2);
	}
	else if (perm == 404)
	{
		ft_putstr_fd("Minishell:", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
	}
}
