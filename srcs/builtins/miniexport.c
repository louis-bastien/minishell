/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniexport.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:12:36 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/04 16:58:53 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_var_res(int outfd, const char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=')
	{
		write(outfd, &var[i], 1);
		i++;
	}
	write(1, "=\"", 2);
	i++;
	while (var[i])
	{
		write(outfd, &var[i], 1);
		i++;
	}
	write(outfd, "\"\n", 2);
}

void	export_no_arg(char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strchr((*env)[i], '='))
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			print_var_res(STDOUT_FILENO, (*env)[i]);
		}
		i++;
	}
}

char	**update_env(char **var_value, t_command *cmd, char ***env, int j)
{
	char	**nenv;
	int		i;

	i = get_var_index(var_value[0], *env);
	if (i == -1)
	{
		nenv = add_str_darry(*env, cmd->args[j]);
	}
	else
		nenv = set_darray(*env, cmd->args[j], i);
	return (nenv);
}

int	mini_export(t_command *cmd, char ***env)
{
	char	**var_value;
	int		i;

	var_value = NULL;
	if (cmd->args_count == 1)
		export_no_arg(env);
	else
	{
		i = 0;
		while (cmd->args[++i])
		{
			if (ft_strchr(cmd->args[i], '=') != NULL)
			{
				var_value = ft_split(cmd->args[i], '=');
				if (is_env_var_valid(var_value[0]) == 1)
					ft_error_perm(42, "export: not a valid identifier\n");
				else if (double_array_size(var_value) > 2)
					ft_error_perm(42, "export: format incorrect\n");
				else
					*env = update_env(var_value, cmd, env, i);
				free(var_value);
			}
		}
	}
	return (0);
}
