/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:19:28 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/04 14:49:58 by lbastien         ###   ########.fr       */
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

char	*get_env_value(char *name, t_state *state)
{
	char	*value;

	if (ft_strlen(name) == 1 && name[0] == '?')
		value = ft_itoa(state->data->exit_status);
	else
		value = getenv(name);
	if (!value)
		value = "";
	return (value);
}

char	*replace_env(char *str, int env_pos, char *value, char *name)
{
	char	*new_str;
	int		new_length;
	int		name_length;

	name_length = ft_strlen(name) + 1;
	new_length = ft_strlen(str) - name_length + ft_strlen(value);
	new_str = malloc(sizeof(char) * (new_length + 1));
	if (!new_str)
		return (NULL);
	strncpy(new_str, str, env_pos);
	new_str[env_pos] = '\0';
	strcat(new_str, value);
	strcat(new_str, str + env_pos + (name_length));
	free (name);
	free(str);
	return (new_str);
}

int	is_valid_env(char c)
{
	if (ft_isalnum(c))
		return (1);
	else if (c == '?')
		return (1);
	else if (c == '_')
		return (1);
	else
		return (0);
}
