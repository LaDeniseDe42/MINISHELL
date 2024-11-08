/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:48:02 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:34 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	nb_line_not_empty(char **parsed)
{
	t_index	i;

	init_index(&i);
	while (parsed[i.a])
	{
		if (ft_strlen(parsed[i.a]) > 0)
			i.b++;
		i.a++;
	}
	return (i.b);
}

void	is_needed(t_readed *r)
{
	char	***align;
	t_index	ex;

	init_index(&ex);
	align = ft_calloc(count_3_tb(r->parsed) + 1, sizeof(char **));
	while (r->parsed[ex.a])
	{
		ex.b = 0;
		ex.c = 0;
		align[ex.a]
			= ft_calloc(nb_line_not_empty(r->parsed[ex.a]) + 1, sizeof(char *));
		while (r->parsed[ex.a][ex.b])
		{
			if (ft_strlen(r->parsed[ex.a][ex.b]) > 0)
				align[ex.a][ex.c++] = ft_strjoin(r->parsed[ex.a][ex.b], "");
			ex.b++;
		}
		ex.a++;
	}
	free_3d_tb(r->parsed);
	r->parsed = align;
}

void	realign_tb_if_needed(t_readed *r)
{
	t_index	ind;

	init_index(&ind);
	while (r->parsed[ind.a])
	{
		ind.b = 0;
		while (r->parsed[ind.a][ind.b])
		{
			if (ft_strlen(r->parsed[ind.a][ind.b]) == 0)
				break ;
			ind.b++;
		}
		if (ind.b == ft_count_tb(r->parsed[ind.a]))
			ind.a++;
		else
			break ;
	}
	if (ind.a != count_3_tb(r->parsed))
	{
		is_needed(r);
	}
}

int	ct_struct_tb_redir(t_redir **re)
{
	t_index	count;

	init_index(&count);
	while (re[count.a])
		count.a++;
	return (count.a);
}

int	ct_struct_redir(t_redir *re)
{
	t_index	de_la_main;

	init_index(&de_la_main);
	while (re[de_la_main.a].redir)
		de_la_main.a++;
	return (de_la_main.a);
}
