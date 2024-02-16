/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:41:27 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/16 10:52:03 by agheredi         ###   ########.fr       */
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
	if (index == (double_array_size(envp) - 1))
		index = -1;
	return (index);
}

char	**add_str_darry(char **d_array, char *nwstr)
{
	char	**nw_darray;
	int		sizeold;
	int		i;

	sizeold = double_array_size(d_array);
	nw_darray = (char **)malloc(sizeof(char *) * (sizeold + 2));
	if (!nw_darray)
		ft_error_perm(42, "Error al asignar memori con Malloc\n");
	i = 0;
	while (i < sizeold)
	{
		nw_darray[i] = ft_strdup(d_array[i]);
		free(d_array[i]);
		i++;
	}
	nw_darray[i] = ft_strdup(nwstr);
	nw_darray[i + 1] = NULL;
	free(d_array);
	return (nw_darray);
}
