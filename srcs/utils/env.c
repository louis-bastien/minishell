/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:41:27 by agheredi          #+#    #+#             */
<<<<<<< HEAD:srcs/utils/env_utils.c
/*   Updated: 2024/02/23 15:27:38 by agheredi         ###   ########.fr       */
=======
/*   Updated: 2024/02/22 22:02:15 by lbastien         ###   ########.fr       */
>>>>>>> main:srcs/utils/env.c
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
		i++;
	}
	nw_darray[i] = ft_strdup(nwstr);
	nw_darray[i + 1] = NULL;
	free_darray(d_array);
	return (nw_darray);
}

<<<<<<< HEAD:srcs/utils/env_utils.c
char	**rm_d_array(char **d_array, int i)
{
	char	**orig_arr;
	char	**new_arr;
	int		orig_arr_size;
	int		j;

	orig_arr = d_array;
	orig_arr_size = double_array_size(orig_arr);
	new_arr = (char **)malloc(sizeof(char *) * orig_arr_size);
	j = 0;
	while (j < i)
	{
		new_arr[j] = ft_strdup(orig_arr[j]);
		j++;
	}
	while (orig_arr[i] && orig_arr[i + 1])
	{
		new_arr[j] = ft_strdup(orig_arr[i + 1]);
		i++;
		j++;
	}
	new_arr[j] = NULL;
	free_darray(d_array);
	return (new_arr);
=======
char	**copy_env(char **env, t_state *state)
{
	char	**data_env;
	int		i;
	int		size_env;

	i = 0;
	size_env = double_array_size(env);
	data_env = (char **)malloc(sizeof(char *) * (size_env + 1));
	if (!data_env)
		ft_exit("Failed to malloc data_env", state);
	i = 0;
	while (i < size_env)
	{
		data_env[i] = ft_strdup(env[i]);
		i++;
	}
	data_env[i] = NULL;
	return (data_env);
>>>>>>> main:srcs/utils/env.c
}
