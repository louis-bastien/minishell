/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:30:36 by agheredi          #+#    #+#             */
/*   Updated: 2023/05/29 11:03:04 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*nextlst;

	if (lst)
	{
		current = *lst;
		while (current)
		{
			nextlst = current -> next;
			ft_lstdelone(current, del);
			current = nextlst;
		}
		*lst = NULL;
	}
}
