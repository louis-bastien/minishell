/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:19:28 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/13 13:39:14 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_name(char *name, int len)
{
	char	*value;
	int		i;

	i = 0;
	while (is_valid_env(name[i]) && len)
		i++;
	value = ft_strndup(name, i);
	if (!value)
		return (NULL);
	return (value);
}

char	*get_env_value(char *name)
{
	char	*value;

	if (ft_strlen(name) == 1 && name[0] == '?')
		value = get_exit_status("exit_status");
	else
		value = getenv(name);
	if (!value)
		value = "";
	return (value);
}

char	*get_exit_status(char *str)
{
	return (str);
}
