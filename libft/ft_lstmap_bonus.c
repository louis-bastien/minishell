/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:59:47 by agheredi          #+#    #+#             */
/*   Updated: 2023/05/29 11:07:45 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*mapped;
	void	*aux;

	newlst = NULL;
	while (lst != NULL)
	{
		aux = f(lst -> content);
		mapped = ft_lstnew(aux);
		if (!mapped)
		{
			ft_lstclear(&newlst, del);
			free(aux);
			return (NULL);
		}
		ft_lstadd_back(&newlst, mapped);
		lst = lst -> next;
	}
	return (newlst);
}
