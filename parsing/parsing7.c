/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:44:31 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/10 15:53:11 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	help_treat_temp2(t_tt *t, t_redir *for_set)
{
	if (t->i < (int)ft_strlen(t->new) && t->new[t->i + 1])
		for_set->redir = ft_calloc(1, 1);
	if (t->i < (int)ft_strlen(t->new) && t->new[t->i + 1])
		for_set->output = ft_calloc(1, 1);
}

void	eternal_reduce_lines_dol(t_readed *r,
			t_index *i, char **str)
{
	char	*search;

	search = ft_calloc(1, 1);
	while (r->readed[i->a] && verif_after_dol(r->readed, i->a) == 1)
		search = add_char(r->readed[i->a++], search);
	i->b = ft_search_env(search, r, 2);
	if (r->export[i->b] && ft_strlen(r->export[i->b]) > ft_strlen(search))
		*str = add_str(ft_strjoin(r->export[i->b]
					+ ft_strlen(search) + 1, ""), *str);
	i->a--;
	free(search);
}

void	parsing_dollar(t_readed *r)
{
	char	*str;
	t_index	i;

	str = ft_calloc(1, 1);
	init_index(&i);
	while (r->readed[i.a])
	{
		flag_state(r->readed, &i.i, i.a);
		if (r->readed[i.a] == '$' && i.i != 1)
		{
			i.a++;
			if (r->readed[i.a] == '?')
				str = add_str(ft_itoa(g_core.err_code), str);
			else if (verif_after_dol(r->readed, i.a) == 1)
				eternal_reduce_lines_dol(r, &i, &str);
			else
				str = add_char(r->readed[--i.a], str);
		}
		else
			str = add_char(r->readed[i.a], str);
		i.a++;
	}
	free(r->readed);
	r->readed = str;
}
