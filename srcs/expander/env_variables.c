/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:19:28 by lbastien          #+#    #+#             */
/*   Updated: 2024/02/01 16:08:39 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_name(char *name)
{
	char	*value;
	int		i;

	i = 0;
	name += 1;
	while (is_valid_env(name[i]))
		i++;
	value = ft_strndup(name, i);
	if (!value)
		return (NULL);
	return (value);
}

char	*get_env_value(char *str, t_state *state)
{
	char	*name;
	char	*value;

	name = get_env_name(str);
	value = NULL;
	if (!name)
		ft_exit("(Expander) Failed to malloc name", state);
	else if (ft_strlen(name) == 1 && name[0] == '?')
	{
		value = get_exit_status("exit_status");
		printf("printing1 %s\n", value);
	}
	else
		value = getenv(name);
	if (!value)
		value = "";
	free (name);
	return (value);
}

char	*get_exit_status(char *str)
{
	return (str);
}
