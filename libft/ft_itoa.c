/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:56:23 by akastler          #+#    #+#             */
/*   Updated: 2023/07/05 14:52:52 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_calclonnb(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static int	ft_calclonllnb(long long int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int				i;
	char			*str;
	unsigned int	nbr;

	i = ft_calclonnb(n);
	str = ft_calloc((ft_calclonnb(n) + 1), sizeof(char));
	i = i - 1;
	if (n < 0)
		nbr = n * -1;
	else
		nbr = n;
	if (str == NULL)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
		str[0] = '-';
	while (nbr > 0)
	{
		str[i--] = 48 + (nbr % 10);
		nbr = nbr / 10;
	}
	return (str);
}

char	*ft_llitoa(long long int n)
{
	int						i;
	char					*str;
	unsigned long long int	nbr;

	i = ft_calclonllnb(n);
	str = ft_calloc((ft_calclonllnb(n) + 1), sizeof(char));
	i = i - 1;
	if (n < 0)
		nbr = n * -1;
	else
		nbr = n;
	if (str == NULL)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
		str[0] = '-';
	while (nbr > 0)
	{
		str[i--] = 48 + (nbr % 10);
		nbr = nbr / 10;
	}
	return (str);
}
