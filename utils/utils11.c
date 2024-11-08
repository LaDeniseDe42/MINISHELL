/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils11.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:39:27 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/10 14:52:04 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	is_space(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	char_in_quotes_whitespace(char *str, int i, int flag)
{
	if (char_in_quotes(str, i, flag, 9) == 1
		&& char_in_quotes(str, i, flag, 10) == 1
		&& char_in_quotes(str, i, flag, 11) == 1
		&& char_in_quotes(str, i, flag, 12) == 1
		&& char_in_quotes(str, i, flag, 13) == 1
		&& char_in_quotes(str, i, flag, 32) == 1)
		return (1);
	return (0);
}
