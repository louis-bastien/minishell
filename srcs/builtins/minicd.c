/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:48:46 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/13 12:54:46 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_dir_var(char **str, char **env)
{
	char	*dir;

	dir = NULL;
	if (!str[1] || (ft_strncmp(str[1], "~", 2) == 0))
	{
		dir = get_var_env("HOME", env);
		if (!dir)
			ft_error_sms("cd HOME not set");
	}
	if (str[1] && (ft_strncmp(str[1], "-", 2) == 0))
	{
		dir = get_var_env("OLDPWD", env);
		if (!dir)
			ft_error_sms("cd OLDPWD not set");
	}
	else
		dir = ft_strdup(str[1]);
	return (dir);
}

int	minicd(t_state *state)
{
	char	*var;

	var = get_dir_var(state->cmd_list->args, state->data->env);
	printf("%s\n", var);
	if (!var)
		return (1);
	if (chdir(var) == -1)
	{
		printf("cd: %s: No such file or directory\n", var);
		return (1);
	}
	free(var);
	//tengo que modificar mi env????
	return (0);
}
