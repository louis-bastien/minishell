/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:48:46 by agheredi          #+#    #+#             */
/*   Updated: 2024/02/02 13:18:31 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	minicd(char *rute, t_state *state)
// {
// 	if (!*rute)
// 	{
// 		if (chdir(get_var_env("HOME", state->data->env)) < 0)
// 			ft_error_sms("Error builtins HOME\n");
// 		return (0);
// 	}
// 	if (*argv == '\0')
// 		return (0);
// 	if (is_relative_dir(*rute) && !is_actual_dir_or_parent(*rute))
// 	{
// 		try_cd_path(*rute, state->data->env);
// 		return (0);
// 	}
// 	if (chdir(*rute) < 0)
// 	{
// 		ft_error_sms("Error builtins ruta relativa\n");
// 		return (1);
// 	}
// }
