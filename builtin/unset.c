/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:04:20 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:35 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_unset_param(char **cmd_tb, int i)
{
	int	j;

	j = 0;
	while (cmd_tb[i])
	{
		while (cmd_tb[i][j])
		{
			if ((cmd_tb[i][0] >= 48 && cmd_tb[i][0] <= 57))
				return (-1);
			if ((cmd_tb[i][j] >= 65 && cmd_tb[i][j] <= 90) ||
				(cmd_tb[i][j] >= 91 && cmd_tb[i][j] <= 122) ||
				(cmd_tb[i][j] >= 48 && cmd_tb[i][j] <= 57) ||
				cmd_tb[i][j] == '_' ||
				(cmd_tb[i][j] == '\'' && (!cmd_tb[i][j - 1]
					|| !cmd_tb[i][j + 1])) ||
				(cmd_tb[i][j] == '\"' && (!cmd_tb[i][j - 1]
					|| !cmd_tb[i][j + 1])))
				j++;
			else
				return (-1);
		}
		j = 0;
		i++;
	}
	return (0);
}

void	unset_to_tb_export(t_readed *mini, char **temp, int i)
{
	int		j;
	char	*buf;

	j = 0;
	if (ft_search_env(temp[i], mini, 2) != ft_count_tb(mini->export))
	{
		while (mini->export[j] != mini->export[ft_search_env(temp[i], mini, 2)])
			j++;
		free(mini->export[j]);
		while (mini->export[j])
		{
			buf = mini->export[j + 1];
			mini->export[j] = buf;
			j++;
		}
	}
	j = 0;
	if (ft_search_env(temp[i], mini, 1) != ft_count_tb(mini->env))
	{
		j = ft_search_env(temp[i], mini, 1);
		if (j != ft_count_tb(mini->env))
			help_unset_tb_export(mini, buf, j);
	}
}

void	help_unset_tb_export(t_readed *mini, char *buf, int j)
{
	free(mini->env[j]);
	while (mini->env[j])
	{
		buf = mini->env[j + 1];
		mini->env[j] = buf;
		j++;
	}
}

void	unset_my_goat(t_readed *mini, char **temp)
{
	int	i;

	i = 1;
	if (!temp[i])
		;
	if (temp[i])
	{
		while (temp[i])
		{
			if (ft_strlen(temp[i]) == 0 || check_unset_param(temp, i) == -1)
			{
				ft_putstr_fd("Minichevre: unset: ", 2);
				ft_putstr_fd(temp[i], 2);
				ft_putstr_fd(": invalid parameter name\n", 2);
			}
			else
				unset_to_tb_export(mini, temp, i);
			i++;
		}
	}
}
