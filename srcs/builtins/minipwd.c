/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minipwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:06:21 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/21 21:39:32 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mini_pwd(t_state *state)
{
	char	*pwd;

	state = NULL;
	pwd = NULL;
	pwd = getcwd(pwd, sizeof(pwd));
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return (0);
}
