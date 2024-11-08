/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:24:30 by akastler          #+#    #+#             */
/*   Updated: 2022/11/18 09:24:49 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew_v2(void *content, void (*del)(void *))
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(*ptr));
	if (!ptr)
	{
		del(content);
		return (0);
	}
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lstfin;
	t_list	*lst2;

	if (!lst || !f || !del)
		return (0);
	lstfin = ft_lstnew_v2(f(lst->content), del);
	if (!lstfin)
		return (0);
	lst2 = lstfin;
	lst = lst->next;
	while (lst != NULL)
	{
		lst2 = ft_lstnew_v2(f(lst->content), del);
		if (!lst2)
		{
			ft_lstclear(&lst2, del);
			ft_lstclear(&lstfin, del);
		}
		lst = lst->next;
		ft_lstadd_back(&lstfin, lst2);
	}
	return (lstfin);
}
