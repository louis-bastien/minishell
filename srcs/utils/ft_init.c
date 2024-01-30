/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:50:25 by agheredi          #+#    #+#             */
/*   Updated: 2024/01/30 12:48:36 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**copy_env(char **env)
{
	int		i;
	int		j;
	char	**data_env;

	i = -1;
	j = 0;
	while (env[++i])
		j++;
	data_env = malloc(sizeof(char *) * (j + 1));
	if (!data_env)
		ft_error_sms("malloc");
	i = 0;
	while (i < j)
	{
		data_env[i] = ft_strdup(env[i]);
		i++;
	}
	data_env[i] = NULL;
	return (data_env);
}
