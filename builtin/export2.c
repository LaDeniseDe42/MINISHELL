/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:42:48 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:35 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(char **str, int i, int j)
{
	int	equal_passed;

	equal_passed = 0;
	while (str[++i])
	{
		printf("declare -x ");
		j = 0;
		while (str[i][j])
		{
			printf("%c", str[i][j]);
			if (str[i][j] == '=' && equal_passed == 0)
			{
				printf("\"");
				equal_passed = 1;
			}
			j++;
		}
		if (equal_passed == 1)
		{
			equal_passed = 0;
			printf("\"");
		}
		printf("\n");
	}
}

void	treat_equal(t_readed *r, char *temp)
{
	int		pos[2];
	int		i;
	char	*search;

	i = 0;
	search = ft_calloc(1, 1);
	while (temp[i])
	{
		if (temp[i] == '=')
			break ;
		search = add_char(temp[i++], search);
	}
	pos[0] = ft_search_env(search, r, 1);
	pos[1] = ft_search_env(search, r, 2);
	if (pos[0] == ft_count_tb(r->env))
		r->env = add_one_line(r->env, temp);
	else
		modify_one_line(r->env, pos[0], temp);
	if (pos[1] == ft_count_tb(r->export))
		r->export = add_one_line(r->export, temp);
	else
		modify_one_line(r->export, pos[1], temp);
	free(search);
}

char	*remove_plus(char *temp)
{
	int		i;
	int		flag;
	char	*copy;

	i = 0;
	flag = 0;
	copy = ft_calloc(1, 1);
	while (temp[i])
	{
		if (temp[i] == '+' && temp[i + 1] && temp[i + 1] == '=' && flag == 0)
		{
			flag = 1;
			i++;
		}
		copy = add_char(temp[i++], copy);
	}
	return (copy);
}

void	add_back_line(t_readed *r, int pos, char *str, int id)
{
	char	*temp;

	(void)r;
	(void)pos;
	if (id == 1)
	{
		temp = r->env[pos];
		r->env[pos]
			= ft_strjoin(r->env[pos], str + pos_of_first_char(str, '=') + 1);
		free(temp);
	}
	else if (id == 2)
	{
		if (ft_strchr(r->export[pos], '=') == NULL)
			r->export[pos] = add_char('=', r->export[pos]);
		temp = r->export[pos];
		r->export[pos]
			= ft_strjoin(r->export[pos], str
				+ pos_of_first_char(str, '=') + 1);
		free(temp);
	}
}

void	treat_plus_equal(t_readed *r, char *temp, int i)
{
	int		pos[2];
	char	*search;
	char	*without_plus;

	search = ft_calloc(1, 1);
	while (temp[i])
	{
		if (temp[i] == '+')
			break ;
		search = add_char(temp[i++], search);
	}
	pos[0] = ft_search_env(search, r, 1);
	pos[1] = ft_search_env(search, r, 2);
	without_plus = remove_plus(temp);
	if (pos[0] == ft_count_tb(r->env))
		r->env = add_one_line(r->env, without_plus);
	else
		add_back_line(r, pos[0], without_plus, 1);
	if (pos[1] == ft_count_tb(r->export))
		r->export = add_one_line(r->export, without_plus);
	else
		add_back_line(r, pos[1], without_plus, 2);
	free(without_plus);
	free(search);
}
