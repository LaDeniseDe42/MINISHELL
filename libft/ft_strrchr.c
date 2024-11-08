/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:02:06 by akastler          #+#    #+#             */
/*   Updated: 2022/11/07 11:04:56 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*temp;

	i = ft_strlen(s);
	temp = (char *)s;
	while (i >= 0)
	{
		if (temp[i] == (char)c)
			return (temp + i);
		i--;
	}
	return (0);
}
