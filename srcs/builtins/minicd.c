/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:48:46 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/14 10:43:45 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_dir_var(t_state *state)
{
	char	*dir;

	dir = NULL;
	if (state->cmd_list->args_count == 1
		|| (ft_strncmp(state->cmd_list->args[1], "~", 2) == 0))
	{
		dir = get_var_env("HOME", state->data->env);
		if (!dir)
			ft_error_sms("cd HOME not set");
	}
	else
		dir = ft_strdup(state->cmd_list->args[1]);
	return (dir);
}

int	minicd(t_state *state)
{
	char	*var;

	var = get_dir_var(state);
	printf("%s\n", var);
	if (!var)
		return (1);
	if (chdir(var) == -1)
	{
		printf("cd: %s: No such file or directory\n", var);
		return (1);
	}
	free(var);
	return (0);
}
