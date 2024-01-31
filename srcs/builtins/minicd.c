/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:48:46 by agheredi          #+#    #+#             */
/*   Updated: 2024/01/31 18:42:55 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	minicd(char **argv, char **envp)
// {
// 	if (!*argv)
// 	{
// 		if (chdir(get_var_env("HOME", envp)) < 0)
// 			ft_error_sms("Error builtins HOME\n");
// 		return (0);
// 	}
// 	if (*argv == '\0')
// 		return (0);
// 	if (is_relative_dir(*argv) && !is_actual_dir_or_parent(*argv))
// 	{
// 		try_cd_path(*argv, envp);
// 		return (0);
// 	}
// 	if (chdir(*argv) < 0)
// 	{
// 		ft_error_sms("Error builtins ruta relativa\n");
// 		return (1);
// 	}
// }
