/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:30:30 by akastler          #+#    #+#             */
/*   Updated: 2022/11/05 13:22:45 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*temp;
	size_t		i;

	i = 0;
	temp = (char *)dest;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		*(char *)temp = *(char *)src;
		temp++;
		src++;
		i++;
	}
	return (dest);
}
