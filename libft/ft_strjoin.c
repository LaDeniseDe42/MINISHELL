/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:28:38 by akastler          #+#    #+#             */
/*   Updated: 2022/11/05 18:40:28 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	lon;
	size_t	lon2;
	char	*str;

	if (s1 && s2)
	{
		lon = ft_strlen(s1);
		lon2 = ft_strlen(s2);
		str = (char *)malloc(sizeof(char) * (lon + lon2 + 1));
		if (str == NULL)
			return (NULL);
		i = 0;
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		i = 0;
		while (s2[i])
			str[lon++] = s2[i++];
		str[lon] = '\0';
		return (str);
	}
	return (NULL);
}
