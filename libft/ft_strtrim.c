/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:54:16 by akastler          #+#    #+#             */
/*   Updated: 2022/11/09 13:51:55 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_calc(char const *s1, char const *set, int is)
{
	int	i;
	int	lon;

	i = 0;
	lon = ft_strlen(s1);
	if (is == 1)
	{
		while (i < lon)
		{
			if (ft_strchr(set, s1[i]) == 0)
				return (i);
			i++;
		}
	}
	else if (is == 2)
	{
		while (i < lon)
		{
			if (ft_strchr(set, s1[lon - i - 1]) == 0)
				return (lon - i);
			i++;
		}
		return (lon - i);
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		debut;
	int		fin;
	char	*str;

	if (!s1)
		return (0);
	if (!set)
		return ((char *)s1);
	debut = ft_calc(s1, set, 1);
	fin = ft_calc(s1, set, 2);
	if (debut >= fin)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (fin - debut + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, s1 + debut, fin - debut + 1);
	return (str);
}
