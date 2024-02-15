/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:41:27 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/15 17:33:59 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	double_array_size(char **d_str)
{
	int	i;

	i = 0;
	while (d_str[i])
		i++;
	return (i);
}

char	**set_darray(char **d_str, char *n_str, int index)
{
	free(d_str[index]);
	d_str[index] = ft_strdup(n_str);
	return (d_str);
}

int	get_var_index(char *var, char **envp)
{
	int	index;
	int	len_var;

	len_var = ft_strlen(var);
	index = 0;
	while (envp[index] != NULL)
	{
		if (ft_strncmp(envp[index], var, len_var) == 0)
			return (index);
		index++;
	}
	if (index == double_array_size(envp))
		index = -1;
	return (index);
}

char	**update_env(char **var_value, t_state *state)
{
	char	**nenv;
	int		i;

	i = get_var_index(var_value[0], state->data->env);
	if (i == -1)
	{
		//quiere decir que la variable no existe y debo crearla
	}
	nenv = set_darray(state->data->env, state->cmd_list->args[1], i);
	return (nenv);
}
