/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:40:13 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/10 14:51:15 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tb_withoutnl(char **tb)
{
	int	i;

	i = 0;
	while (tb[i])
	{
		printf("%s", tb[i]);
		if (tb[i + 1])
			printf(" ");
		i++;
	}
}

int	ft_isnum(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
		{
			if (str[i] == '+' || str[i] == '-')
			{
				if (flag == 1)
					return (-1);
			}
			else
				return (-1);
		}
		i++;
		flag = 1;
	}
	return (1);
}

char	*ft_strlow(char *str)
{
	char	*new_str;
	int		i;

	if (!str)
		return (NULL);
	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	while (str[i])
	{
		new_str[i] = ft_tolower(str[i]);
		i++;
	}
	return (new_str);
}

int	good_cara(char **temp)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (temp[i])
	{
		j = 0;
		while (temp[i][j] && temp[i][j] != '=')
		{
			if ((temp[i][j] >= 65 && temp[i][j] <= 90) ||
				(temp[i][j] >= 91 && temp[i][j] <= 122) || temp[i][j] == '$' ||
				temp[i][j] == '\'' || temp[i][j] == '\"'
					|| ((temp[i][j] >= '0' && temp[i][j] <= '9' && j > 0))
					|| (temp[i][j] == '+' && temp[i][j + 1] == '=' && j > 0))
				;
			else
				return (1);
			j++;
		}
		if (j == 0)
			return (1);
		i++;
	}
	return (0);
}

char	**add_one_line(char **old_tb, char *new_line_to_add)
{
	int		i;
	char	**buf;

	i = 0;
	buf = ft_calloc(ft_count_tb(old_tb) + 2, sizeof(char *));
	while (i < ft_count_tb(old_tb))
	{
		buf[i] = ft_strjoin(old_tb[i], "");
		i++;
	}
	buf[i] = ft_strjoin(new_line_to_add, "");
	free_tb(old_tb);
	return (buf);
}
