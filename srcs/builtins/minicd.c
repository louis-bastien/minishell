/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:48:46 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/09 20:55:59 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	minicd(t_state *state)
{
	char	*var;

	var = get_var_env("HOME", state->data->env);
	if (!state->cmd_list->args[0])
	{
		if (chdir(var) < 0)
			ft_error_sms("Error builtins HOME\n");
		return (0);
	}
	if (state->cmd_list->args[0] == NULL)
		return (0);
	/*if (is_relative_dir(state->cmd_list->args[0])
		&& !is_actual_dir_or_parent(state->cmd_list->args[0]))
	{
		try_cd_path(state->cmd_list->args[0], state->data->env);
		return (0);
	}*/
	if (chdir(state->cmd_list->args[0]) < 0)
	{
		ft_error_sms("Error builtins ruta relativa\n");
		return (1);
	}
	return (0);
}
