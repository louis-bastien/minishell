/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniexport.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:12:36 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/23 20:25:42 by agusheredia      ###   ########.fr       */
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

void	export_no_arg(t_command *cmd, char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strchr((*env)[i], '='))
		{
			ft_putstr_fd("declare -x ", cmd->fd_out);
			print_var_res(cmd->fd_out, (*env)[i]);
		}
		i++;
	}
}

char	**update_env(char **var_value, t_command *cmd, char ***env)
{
	char	**nenv;
	int		i;

	i = get_var_index(var_value[0], *env);
	if (i == -1)
	{
		nenv = add_str_darry(*env, cmd->args[1]);
	}
	else
		nenv = set_darray(*env, cmd->args[1], i);
	return (nenv);
}

int	mini_export(t_command *cmd, char ***env)
{
	char	**var_value;

	var_value = NULL;
	if (cmd->args_count == 1)
		export_no_arg(cmd, env);
	else
	{
		if (ft_strchr(cmd->args[1], '=') != NULL)
		{
			var_value = ft_split(cmd->args[1], '=');
			if (double_array_size(var_value) != 2)
				ft_error_perm(42, "export: format incorrect\n");
			*env = update_env(var_value, cmd, env);
		}
		else
			ft_error_perm(42, "export: format incorrect\n");
	}
	return (0);
}
