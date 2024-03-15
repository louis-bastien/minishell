/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minipwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:06:21 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/15 15:23:02 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mini_pwd(char ***env, int fd_out)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, sizeof(pwd));
	if (!pwd)
	{
		pwd = get_var_env("PWD=", *env);
		ft_putstr_fd(pwd, fd_out);
		ft_putstr_fd("\n", fd_out);
		return (0);
	}
	ft_putendl_fd(pwd, fd_out);
	free(pwd);
	return (0);
}
