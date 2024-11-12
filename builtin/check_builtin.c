/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:08:01 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/10 15:17:00 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(t_readed *r, int cmd_nbr)
{
	char	**temp;
	int		i;

	i = 0;
	temp = r->new_parsed[cmd_nbr];
	if (temp[0] && ft_strncmp("exit", temp[0], 5) == 0)
	{
		help_exit(r, temp, 0);
		i = 1;
	}
	else if (temp[0] && ft_strncmp("export", temp[0], 7) == 0)
	{
		help_export(r, temp);
		i = 1;
	}
	else if (temp[0] && ft_strncmp("unset", temp[0], 5) == 0)
	{
		help_unset(r, temp);
		i = 1;
	}
	else
		i = check_build_two(temp, r, NULL);
	return (i);
}

int	check_build_two(char **temp, t_readed *r, char *min)
{
	if (temp[0])
		min = ft_strlow(temp[0]);
	if (min && ft_strncmp("pwd", min, 4) == 0)
	{
		free(min);
		return (pwd());
	}
	else if (min && ft_strncmp("cd", min, 3) == 0)
	{
		free(min);
		return (help_cd(r, temp));
	}
	else if (min && ft_strncmp("echo", min, 5) == 0)
	{
		free(min);
		return (help_echo(temp, r));
	}
	else if (min && ft_strncmp("env", min, 4) == 0)
	{
		free(min);
		help_env(r, temp);
		return (1);
	}
	free(min);
	return (0);
}

int	ft_isnum_valid(char *str)
{
	int		i;
	int		j;
	char	*test;

	i = 0;
	j = 0;
	test = ft_llitoa(ft_atolli(str));
	if (str[i] == ' ' || str[i] == '+' || (str[i] >= 9 && str[i] <= 13))
		while (str[i] == ' ' || str[i] == '+' || (str[i] >= 9 && str[i] <= 13))
			i++;
	while (str[i] != ' ' && str[i] != '\0')
	{
		if (str[i] != test[j])
		{
			free(test);
			return (-1);
		}
		i++;
		j++;
	}
	free(test);
	return (0);
}

void	help_exit(t_readed *r, char **temp, long long int idk)
{
	printf("exit\n");
	if (ft_count_tb(temp) > 2)
		reduce_help_exit();
	else
	{
		if (temp[1])
		{
			if (ft_isnum(temp[1]) == 1 && ft_isnum_valid(temp[1]) == 0)
				idk = ft_atolli(temp[1]);
			else
			{
				if (ft_isnum(temp[1]) == -1 || ft_strlen(temp[1]) >= 19)
				{
					ft_putstr_fd("Minishell: exit: ", 2);
					ft_putstr_fd(temp[1], 2);
					ft_putstr_fd(": numeric argument required\n", 2);
				}
				idk = 255;
			}
		}
		else
			idk = 0;
		free_tb(temp);
		exit_the_goat(r, idk);
	}
}
