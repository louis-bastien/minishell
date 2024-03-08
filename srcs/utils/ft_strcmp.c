/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:58:40 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/08 15:22:59 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	if (!str1 || !str2)
		return (1);
	if (ft_strlen(str1) == ft_strlen(str2) - 1)
	{
		if (!ft_strncmp(str1, str2, ft_strlen(str1)))
			return (0);
	}
	return (1);
}
