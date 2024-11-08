/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 08:54:14 by akastler          #+#    #+#             */
/*   Updated: 2022/11/14 14:00:29 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!haystack && !len)
		return (0);
	if (((char *)needle)[j] == '\0')
		return (((char *)haystack));
	while (((char *)haystack)[i] && i < len)
	{
		while (((char *)haystack)[i + j] == ((char *)needle)[j]
			&& ((char *)haystack)[j + i] != '\0' && (i + j) < len)
		{
			j++;
		}
		if (needle[j] == '\0')
		{
			return (((char *)haystack) + i);
		}
		i++;
		j = 0;
	}
	return (0);
}
