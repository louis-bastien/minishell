/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minipwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:06:21 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/13 13:23:35 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mini_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, sizeof(pwd));
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (0);
}
