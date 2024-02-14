/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minipwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:06:21 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/14 10:48:03 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mini_pwd(t_state *state)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, sizeof(pwd));
	ft_putendl_fd(pwd, state->cmd_list->fd_out);
	return (0);
}
