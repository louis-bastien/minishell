/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_darray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:54:48 by agusheredia       #+#    #+#             */
/*   Updated: 2024/03/04 15:22:47 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_darray(char **d_array)
{
	int	i;
	int	size;

	i = 0;
	size = double_array_size(d_array);
	while (i < size)
	{
		free(d_array[i]);
		i++;
	}
	free(d_array);
}
