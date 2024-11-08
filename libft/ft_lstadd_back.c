/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:23:59 by akastler          #+#    #+#             */
/*   Updated: 2022/11/18 09:25:05 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;
	t_list	**cpylst;

	cpylst = lst;
	if (!cpylst)
		return ;
	if (*cpylst == 0)
		*cpylst = new;
	else
	{
		temp = ft_lstlast(*cpylst);
		temp->next = new;
	}
}
