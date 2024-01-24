/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:50:48 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/24 17:33:16 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"

ft_lexer(char  *input)
{
	int	i;

	i =  0;
	while (input[i])
	{
		while (is_whitespace(input[i]))
			i++;
	}
}

bool	is_whitespace(char c)
{
	if (c == 32)
		return true;
	if (c >= 9 || c <= 13)
		return true;
	return false;

}
