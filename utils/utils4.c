/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:54:05 by akastler          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:35 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_quotes(char **export)
{
	int		i;
	char	**buf;
	char	*str;

	i = 0;
	str = "\"";
	buf = ft_calloc(ft_count_tb(export) + 1, sizeof(char *));
	while (export[i] && i < ft_count_tb(export))
	{
		if (export[i] && ft_strchr(export[i], '=')
			&& ft_strchr(export[i], 34) == 0)
			add_quotes_helper(i, buf, export, str);
		else
			buf[i] = ft_strjoin(export[i], "");
		i++;
	}
	free_tb(export);
	return (buf);
}

void	add_quotes_helper(int i, char **buf, char **export, char *str)
{
	int		k;
	int		j;
	char	*temp;
	int		flag;

	k = 0;
	j = 0;
	flag = 0;
	buf[i] = ft_calloc(ft_strlen(export[i]) + 3, sizeof(char));
	while (export[i][j])
	{
		if (j > 0 && export[i][j - 1] && export[i][j - 1] == '=' && flag == 0)
		{
			flag = 1;
			buf[i][k++] = 34;
		}
		buf[i][k] = export[i][j];
		j++;
		k++;
	}
	if (export[i][j] == '\0' && export[i][j - 1] == '=' && flag == 0)
		buf[i][k] = '\"';
	temp = buf[i];
	buf[i] = ft_strjoin(buf[i], str);
	free(temp);
}

void	free_tb(char **paths)
{
	int	line;

	line = 0;
	while (paths[line])
	{
		if (paths[line])
			free(paths[line]);
		line++;
	}
	free(paths);
}

void	ft_print_tb(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		printf("%s\n", str[i++]);
}

int	count_3_tb(char ***tb)
{
	int	i;

	i = 0;
	while (tb[i])
	{
		i++;
	}
	return (i);
}
