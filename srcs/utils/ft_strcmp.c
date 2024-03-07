/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:58:40 by lbastien          #+#    #+#             */
/*   Updated: 2024/03/07 12:26:36 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	if (ft_strlen(str1) == ft_strlen(str2) - 1)
	{
		if (!ft_strncmp(str1, str2, ft_strlen(str1)))
			return (0);
	}
	return (1);
}
