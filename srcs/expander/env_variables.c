/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:19:28 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/19 18:31:27 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_name(char *name, int len)
{
	char	*value;
	int		i;

	i = 0;
	if (name[i] == '?')
		i++;
	else
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
	char	*tmp;

	tmp = NULL;
	if (ft_strlen(name) == 1 && name[0] == '?')
	{
		if (g_signal_received)
			value = ft_itoa(g_signal_received + 128);
		else
			value = ft_itoa(state->data->exit_status);
	}
	else
	{
		tmp = ft_strjoin(name, "=");
		value = get_var_env(tmp, state->data->env);
		free(tmp);
	}
	if (!value)
		value = ft_strdup("");
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
