/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_darray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:54:48 by agusheredia       #+#    #+#             */
/*   Updated: 2024/02/22 21:02:23 by agusheredia      ###   ########.fr       */
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
