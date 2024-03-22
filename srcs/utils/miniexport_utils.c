/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniexport_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:12:05 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/22 13:07:41 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdupapend(char *var)
{
	int		i;
	char	*nwvar;
	int		len;

	i = 0;
	len = ft_strlen(var);
	nwvar = (char *)malloc(sizeof(char) * len);
	while (var[i] != '+' && var[i + 1] != '\0')
	{
		nwvar[i] = var[i];
		i++;
	}
	nwvar[i] = '\0';
	free(var);
	return (nwvar);
}

char	**ft_apend_var(char **env, char **var_value)
{
	char	**nenv;
	char	*exist_value;
	char	*new_value;
	int		i;

	i = get_var_index(var_value[0], env);
	if (i == -1)
	{
		if (!var_value[1])
			exist_value = ft_strdup("=");
		else
			exist_value = ft_strjoin("=", var_value[1]);
		new_value = ft_strjoin(var_value[0], exist_value);
		nenv = addarray(env, new_value);
	}
	else
	{
		exist_value = ft_strdup(env[i]);
		new_value = ft_strjoin(exist_value, var_value[1]);
		free(env[i]);
		env[i] = new_value;
		nenv = env;
	}
	free(exist_value);
	return (nenv);
}

int	ft_export_apend(t_command *cmd, char ***env, char **var_value, int i)
{
	if (var_value[0][ft_strlen(var_value[0]) - 1] == '+')
	{
		var_value[0] = ft_strdupapend(var_value[0]);
		if (is_env_var_valid(var_value[0]) == 1)
		{
			ft_error_builtin(1, cmd->command, cmd->args[i]);
			return (1);
		}
		else
			*env = ft_apend_var(*env, var_value);
	}
	else
	{
		ft_error_builtin(1, cmd->command, cmd->args[i]);
		return (1);
	}
	return (0);
}

char	**addexport(char **d_array, char *nwstr)
{
	char	**nw_darray;
	int		sizeold;
	int		i;
	int		flag;

	flag = 0;
	sizeold = double_array_size(d_array);
	nw_darray = (char **)malloc(sizeof(char *) * (sizeold + 2));
	if (!nw_darray)
		ft_error_perm(42, "Error al asignar memori con Malloc\n");
	i = 0;
	while (i < sizeold)
	{
		if (ft_strncmp(d_array[i], nwstr, ft_strlen(d_array[i])) == 0)
			flag = 1;
		nw_darray[i] = ft_strdup(d_array[i]);
		i++;
	}
	if (flag == 0)
		nw_darray[i++] = ft_strdup(nwstr);
	nw_darray[i] = NULL;
	free_darray(d_array);
	return (nw_darray);
}
