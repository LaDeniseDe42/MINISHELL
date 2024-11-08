/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 10:32:17 by akastler          #+#    #+#             */
/*   Updated: 2022/11/07 09:26:49 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*str;
	char	*dest;

	i = 0;
	str = (char *)src;
	dest = (char *)dst;
	if (!dest && !str)
		return (0);
	else if (dest > str)
	{
		while (len-- > 0)
			dest[len] = str[len];
	}
	else
	{
		while (i < len)
		{
			dest[i] = str[i];
			i++;
		}
	}
	return (dst);
}
