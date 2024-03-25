/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minipwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:06:21 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/25 13:36:56 by lbastien         ###   ########.fr       */
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
		ft_putendl_fd(pwd, fd_out);
	}
	else
		ft_putendl_fd(pwd, fd_out);
	free(pwd);
	return (0);
}
