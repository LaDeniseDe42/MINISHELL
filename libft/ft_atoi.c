/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:46:35 by akastler          #+#    #+#             */
/*   Updated: 2023/07/05 14:53:16 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	signe;

	i = 0;
	j = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		j = (str[i] - '0') + (j * 10);
		i++;
	}
	if (signe == -1)
		return (-j);
	return (j);
}

long long int	ft_atolli(const char *str)
{
	int				i;
	long long int	j;
	int				signe;

	i = 0;
	j = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		j = (str[i] - '0') + (j * 10);
		i++;
	}
	if (signe == -1)
		return (-j);
	return (j);
}
