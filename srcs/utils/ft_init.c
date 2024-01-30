/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:50:25 by agheredi          #+#    #+#             */
/*   Updated: 2024/01/30 11:27:15 by agheredi         ###   ########.fr       */
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
		ft_error_sms(strerror(ENOMEN));
	i = 0;
	while (i < j)
	{
		data_env[i] = ft_strdup(env[i]);
		i++;
	}
	data_env[i] = NULL;
	return (data_env);
}
