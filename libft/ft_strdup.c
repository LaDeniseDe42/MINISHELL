/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:38:06 by akastler          #+#    #+#             */
/*   Updated: 2022/11/05 15:10:24 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*temp;
	int		i;
	int		lon;

	lon = 0;
	i = 0;
	while (s1[lon] != '\0')
		lon++;
	temp = (char *)malloc(sizeof(char) * (lon + 1));
	if (temp == NULL)
		return (NULL);
	while (i < lon)
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
