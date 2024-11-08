/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:03:48 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/10 14:42:22 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_my_goat(t_readed *r, char **temp)
{
	if (temp[1] && ft_strlen(temp[1]) && good_cara(temp) != 1)
	{
		add_export_to_env(r, temp);
		r->export = ft_sort_tb_alpha(r->export);
		g_core.err_code = 0;
	}
	else if (!temp[1])
		print_export(r->export, -1, 0);
	else
	{
		ft_putstr_fd("Minichevre: export: ", 2);
		ft_putstr_fd(r->new_parsed[0][1], 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		g_core.err_code = 1;
	}
}

void	help_export_whith_plus(t_readed *r, char **temp,
	t_add_export_to_env *a, char *temp2)
{
	if (a->flag == 1)
	{
		if (r->env[a->k])
		{
			temp2 = r->env[a->k];
			r->env[a->k] = ft_strjoin(r->env[a->k], a->buff[1]);
			free(temp2);
		}
		if (r->export[a->ret])
		{
			if (r->export[a->ret][ft_strlen(r->export[a->ret]) - 1] == '\"')
				r->export[a->ret][ft_strlen(r->export[a->ret]) - 1] = '\0';
			temp2 = temp[a->i];
			if (ft_strchr(r->export[a->ret], '=') == NULL)
				r->export[a->ret] = add_char('=', r->export[a->ret]);
			temp[a->i] = ft_strjoin(r->export[a->ret], temp[a->i]
					+ ft_strlen(a->buff[0]) + 1);
			free(temp2);
			a->flag = 0;
		}
	}
}

int	pos_of_first_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

void	add_export_to_env(t_readed *r, char **temp)
{
	t_add_export_to_env	a;

	init_add_export_struct(&a);
	while (temp[++a.i])
	{
		if (ft_strchr(temp[a.i], '='))
		{
			if (temp[a.i][pos_of_first_char(temp[a.i], '=') - 1] == '+')
				treat_plus_equal(r, temp[a.i], 0);
			else
				treat_equal(r, temp[a.i]);
		}
		else if (ft_strchr(temp[a.i], '=') == NULL
			&& ft_search_env(temp[a.i], r, 2) == ft_count_tb(r->export))
			r->export = add_one_line(r->export, temp[a.i]);
	}
}
