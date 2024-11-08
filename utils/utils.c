/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:32:50 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/10 15:29:50 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_second_quote(char *line, int i, int *nb_q, int quotes)
{
	int	j;

	j = i + 1;
	*nb_q += 1;
	while (line[j] && line[j] != quotes)
		j++;
	if (line[j] == quotes)
		*nb_q += 1;
	return (j - i);
}

int	count_quotes(char *line)
{
	int	i;
	int	single_q;
	int	double_q;

	i = 0;
	single_q = 0;
	double_q = 0;
	if (ft_strchr(line, '\"') == NULL && ft_strchr(line, '\'') == NULL)
		return (1);
	while (line[i])
	{
		if (line [i] == '\'')
			i += find_second_quote(line, i, &single_q, '\'');
		if (line[i] == '\"')
			i += find_second_quote(line, i, &double_q, '\"');
		if (i < (int)ft_strlen(line))
			i++;
		else
			break ;
	}
	if ((double_q > 0 && double_q % 2 != 0)
		|| (single_q > 0 && single_q % 2 != 0))
		return (0);
	return (1);
}

int	char_in_quotes(char *str, int i, int flag, char c)
{
	if (str[i] == c)
	{
		if (flag == 2 || flag == 1)
			return (1);
		return (0);
	}
	return (1);
}

void	print_3d_tb(char ***tb)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tb[i])
	{
		j = 0;
		while (tb[i][j])
		{
			printf("tb[%d][%d] = %s\n", i, j, tb[i][j]);
			j++;
		}
		i++;
	}
}

void	free_3d_tb(char ***tb)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tb[i])
	{
		j = 0;
		while (tb[i][j])
		{
			if (tb[i][j])
				free(tb[i][j]);
			j++;
		}
		free(tb[i]);
		i++;
	}
	free(tb);
	tb = NULL;
}
