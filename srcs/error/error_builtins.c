/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:20:02 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/16 20:40:48 by agusheredia      ###   ########.fr       */
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

void	ft_error_open(int perm, char *arg)
{
	if (perm == 55)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	else if (perm == 1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (perm == 404)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

void	exit_error(int perm, char *cmd, t_state *state)
{
	if (perm == NOCMD || perm == 404)
		state->data->exit_status = 127;
	state->to_stop = true;
	ft_error_perm(perm, cmd);
}
