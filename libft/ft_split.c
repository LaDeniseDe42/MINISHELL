/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:34:38 by akastler          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:36 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_tb(char **tb)
{
	int	i;

	i = 0;
	if (!tb)
		return (NULL);
	while (tb[i])
	{
		free(tb[i]);
		i++;
	}
	free(tb);
	return (NULL);
}

static size_t	ft_word(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[k])
	{
		if (s[k] != c && j == 0)
		{
			j = 1;
			i++;
		}
		else if (s[k] == c)
			j = 0;
		k++;
	}
	return (i);
}

static char	*ft_dupv2(char const *str, char c, size_t start)
{
	char	*s1;
	size_t	end;
	int		i;

	end = start;
	i = 0;
	while (str[end] != c && str[end])
		end++;
	s1 = (char *)ft_calloc((end - start + 1), sizeof(char));
	if (!s1)
		return (NULL);
	while (start < end && str[start])
	{
		s1[i++] = str[start++];
	}
	return (s1);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	str = ft_calloc((ft_word(s, c) + 1), sizeof(char *));
	if (!str)
		return (free_tb(str));
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (j < ft_word(s, c))
		{
			str[j] = ft_dupv2(s, c, i);
			if (str[j++] == 0)
				return (free_tb(str));
		}
		while (s[i] && s[i] != c)
			i++;
	}
	return (str);
}
