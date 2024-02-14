/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniexport.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:12:36 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/14 12:11:20 by agheredi         ###   ########.fr       */
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

//void	update_env(char **var_value, t_state *state)

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
			//update_env(var_value, state);
		}
		else
		{
			printf("export: format incorrect %s", state->cmd_list->args[1]);
			return (1);
		}
	}
	return (0);
}
