/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniexport.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:12:36 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/15 17:10:12 by agheredi         ###   ########.fr       */
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

void	export_no_arg(t_state *state)
{
	int	i;

	i = 0;
	while (state->data->env[i])
	{
		if (ft_strchr(state->data->env[i], '='))
		{
			ft_putstr_fd("declare -x ", state->cmd_list->fd_out);
			print_var_res(state->cmd_list->fd_out, state->data->env[i]);
		}
		i++;
	}
}


int	mini_export(t_state *state)
{
	char	**var_value;

	var_value = NULL;
	if (state->cmd_list->args_count == 1)
		export_no_arg(state);
	else
	{
		if (ft_strchr(state->cmd_list->args[1], '=') != NULL)
		{
			var_value = ft_split(state->cmd_list->args[1], '=');
			if (double_array_size(var_value) != 2)
				ft_error_perm(42, "export: format incorrect\n");
			printf("variable %s \n", var_value[0]);
			printf("valor %s\n", var_value[1]);
			state->data->env = update_env(var_value, state);
		}
		else
			ft_error_perm(42, "export: format incorrect\n");
	}
	return (0);
}
