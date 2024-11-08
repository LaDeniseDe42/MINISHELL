/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:24:11 by akastler          #+#    #+#             */
/*   Updated: 2022/11/18 09:25:01 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*end;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		end = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = end;
	}
}
