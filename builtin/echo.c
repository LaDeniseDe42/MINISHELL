/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:02:29 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/06 17:42:27 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_echo(char **args, t_readed *mini)
{
	int	i;

	i = 1;
	(void)mini;
	if (!args[1])
		printf("\n");
	else if (n_or_other(args[1]) == 0)
	{
		while (args[i] && n_or_other(args[i]) == 0)
			i++;
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i] && (args[i + 1]))
				printf(" ");
			i++;
		}
	}
	else
		help_echo_line(args, i);
}

void	help_echo_line(char **args, int i)
{
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}

int	n_or_other(char *args)
{
	int	j;

	j = 0;
	if (args[0] != '-')
		return (1);
	j++;
	if (!args[j])
		return (1);
	if (args[j])
	{
		while (args[j])
		{
			if (args[j] != 'n')
				return (1);
			j++;
		}
	}
	return (0);
}

char	*prep_echo(char *line)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	ft_strlcpy(str, line, ft_strlen(line) + 1);
	while (str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
			{
				if (str[i] == ' ')
					str[i] = 9;
				i++;
			}
		}
		i++;
	}
	return (str);
}

char	*prep_echo_2(char *line)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	if (line)
	{
		str = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		ft_strlcpy(str, line, ft_strlen(line) + 1);
		while (str[i])
		{
			if (str[i] == '\"')
			{
				i++;
				while (str[i] && str[i] != '\"')
				{
					if (str[i] == 9)
						str[i] = ' ';
					i++;
				}
			}
			i++;
		}
	}
	return (str);
}
