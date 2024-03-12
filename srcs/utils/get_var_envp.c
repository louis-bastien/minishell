/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:24:37 by agheredi          #+#    #+#             */
/*   Updated: 2024/03/12 13:27:14 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_var_env(char *var, char **envp)
{
	char	*str_var;
	int		len_var;

	str_var = NULL;
	len_var = ft_strlen(var);
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, var, len_var) == 0)
		{
			str_var = ft_strdup(*envp + (len_var));
			break ;
		}
		envp++;
	}
	return (str_var);
}
