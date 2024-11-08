/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:38:23 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:35 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_sort_tb_alpha(char **tb)
{
	char	*temp;
	int		i;
	int		nb_line;

	i = 0;
	if (!tb)
		return (0);
	nb_line = ft_count_tb(tb);
	while (i < nb_line)
	{
		if (tb[i + 1])
		{
			if (ft_strcmp(tb[i], tb[i + 1]) > 0)
			{
				temp = tb[i];
				tb[i] = tb[i + 1];
				tb[i + 1] = temp;
			}
		}
		i++;
		if (i == nb_line - 1 && ft_tb_sorted(tb) == 0)
			i = 0;
	}
	return (tb);
}

int	ft_count_tb(char **tb)
{
	int	i;

	i = 0;
	while (tb[i])
		i++;
	return (i);
}

int	ft_tb_sorted(char **tb)
{
	int	nb_line;
	int	i;

	i = 0;
	nb_line = ft_count_tb(tb);
	while (i < nb_line)
	{
		if (tb[i + 1] == NULL)
			return (1);
		if (ft_strcmp(tb[i], tb[i + 1]) <= 0)
			i++;
		else
		{
			return (0);
		}
	}
	return (1);
}

char	**ft_copy_tb(char **tb)
{
	char	**cpy_tb;
	int		nb_line;
	int		i;

	nb_line = 0;
	i = 0;
	cpy_tb = NULL;
	while (tb[nb_line])
		nb_line++;
	cpy_tb = ft_calloc(nb_line + 1, sizeof(char *));
	nb_line = 0;
	while (tb[nb_line])
	{
		i = 0;
		cpy_tb[nb_line] = ft_calloc(ft_strlen(tb[nb_line]) + 1, sizeof(char));
		while (tb[nb_line][i])
		{
			cpy_tb[nb_line][i] = tb[nb_line][i];
			i++;
		}
		nb_line++;
	}
	return (cpy_tb);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2 || ft_strlen(s1) == 0 || ft_strlen(s2) == 0)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
