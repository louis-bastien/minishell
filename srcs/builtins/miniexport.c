/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniexport.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:12:36 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/23 17:24:22 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_var_res(const char *var, int fd_out)
{
	char	**var_print;

	var_print = ft_split(var, '=' );
	ft_putstr_fd(var_print[0], fd_out);
	ft_putstr_fd("=\"", fd_out);
	ft_putstr_fd(var_print[1], fd_out);
	ft_putstr_fd("\"\n", fd_out);
	free_darray(var_print);
}

void	export_no_arg(char ***env, char **var_export, int fd_out)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strchr((*env)[i], '='))
		{
			ft_putstr_fd("declare -x ", fd_out);
			print_var_res((*env)[i], fd_out);
		}
		i++;
	}
	i = 0;
	if (var_export)
	{
		while (var_export[i])
		{
			ft_putstr_fd("declare -x ", fd_out);
			ft_putendl_fd(var_export[i], fd_out);
			i++;
		}
	}
}

char	**update_env(char **var_value, t_command *cmd, char ***env, int j)
{
	char	**nenv;
	int		i;

	i = get_var_index(var_value[0], *env);
	if (i == -1)
	{
		nenv = addarray(*env, cmd->args[j]);
	}
	else
		nenv = set_darray(*env, cmd->args[j], i);
	return (nenv);
}

int	is_var_to_update(char *arg, t_command *cmd, char ***env, int i)
{
	int		status;
	char	**var_value;
	char	*str;

	status = 0;
	str = NULL;
	var_value = ft_split(arg, '=');
	if (is_env_var_valid(var_value[0]) == 1)
		status = ft_export_apend(cmd, env, var_value, i);
	else if (double_array_size(var_value) > 2)
	{
		str = ft_memchr(arg, '=', ft_strlen(arg));
		var_value[1] = ft_strdup(str++);
		*env = update_env(var_value, cmd, env, i);
	}
	else
		*env = update_env(var_value, cmd, env, i);
	free_darray(var_value);
	return (status);
}

int	mini_export(t_command *cmd, t_state *state, char ***env, int fd_out)
{
	int		i;
	int		status;

	status = 1;
	if (cmd->args_count == 1)
		export_no_arg(env, state->data->vexp, fd_out);
	else
	{
		i = 1;
		while (cmd->args[i])
		{
			if (ft_strchr(cmd->args[i], '=') != NULL)
				status = is_var_to_update(cmd->args[i], cmd, env, i);
			else if (is_env_var_valid(cmd->args[i]) == 0)
				state->data->vexp = addexport(state->data->vexp, cmd->args[i]);
			else if (is_env_var_valid(cmd->args[i]) == 1)
				ft_error_builtin(1, cmd->command, cmd->args[i]);
			i++;
		}
	}
	return (status);
}
