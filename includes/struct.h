/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbastien <lbastien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:28:07 by lbastien          #+#    #+#             */
/*   Updated: 2024/01/24 16:47:45 by lbastien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum s_token
{
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
	PIPE,
}	t_token;

typedef struct s_item
{
	char			*str;
	t_token			token;
	int				index;
	struct s_item	*next;
}	t_item;

#endif