/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:12:00 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:35 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shit_bag(t_treat_redir *tr, t_redir *for_set)
{
	for_set->redir = ft_calloc(1, 1);
	for_set->output = ft_calloc(1, 1);
	tr->temp = ft_calloc(1, 1);
	tr->temp = add_str(ft_strjoin(tr->tb_cpy[tr->i] + tr->z, ""), tr->temp);
	tr->tb_cpy[tr->i][tr->z] = '\0';
}

void	while_treat_temp(t_pars *pars, t_tt *t,
	t_redir *for_set, t_readed *r)
{
	int	i;

	i = 0;
	while (t->new[i])
	{
		t->c = t->new[i];
		flag_state(t->new, &t->pirate_flag, i);
		while (t->new[i] && t->new[i] == t->c)
			for_set->redir = add_char(t->new[i++], for_set->redir);
		while (t->new[i])
		{
			flag_state(t->new, &t->pirate_flag, i);
			if ((t->new[i] == '>'
					|| t->new[i] == '<') && t->pirate_flag == 0)
				break ;
			for_set->output = add_char(t->new[i++], for_set->output);
		}
		r->re[pars->index.i][pars->index.c] = *for_set;
		if (i < (int)ft_strlen(t->new) && t->new[i + 1])
		{
			for_set->redir = ft_calloc(1, 1);
			for_set->output = ft_calloc(1, 1);
		}
		pars->index.c++;
	}
}

void	help_while_treat_temp2(t_pars *pars, t_treat_redir *tr,
	t_tt *t, t_readed *r)
{
	int		w;
	char	*temp;

	w = 0;
	(void)pars;
	(void)r;
	t->new = ft_strjoin(tr->temp, "");
	if (t->new[ft_strlen(t->new) - 1] == '<'
		|| t->new[ft_strlen(t->new) - 1] == '>')
	{
		while (anything_after_redir(t->new, ft_strlen(t->new)) == 0)
		{
			if (tr->tb_cpy[tr->i + w])
			{
				temp = t->new;
				t->new = ft_strjoin(t->new, tr->tb_cpy[tr->i + w]);
				free(temp);
				tr->tb_cpy[tr->i + w][0] = '\0';
				w++;
			}
			else
				break ;
		}
	}
}

void	while_treat_temp2(t_pars *pars, t_treat_redir *tr,
	t_redir *for_set, t_readed *r)
{
	t_tt	t;

	init_ttt(&t);
	help_while_treat_temp2(pars, tr, &t, r);
	while (t.new[t.i])
	{
		t.c = t.new[t.i];
		flag_state(t.new, &t.pirate_flag, t.i);
		while (t.new[t.i] && t.new[t.i] == t.c)
			for_set->redir = add_char(t.new[t.i++], for_set->redir);
		while (t.new[t.i])
		{
			flag_state(t.new, &t.pirate_flag, t.i);
			if ((t.new[t.i] == '>'
					|| t.new[t.i] == '<') && t.pirate_flag == 0)
				break ;
			for_set->output = add_char(t.new[t.i++], for_set->output);
		}
		r->re[pars->index.i][pars->index.c++] = *for_set;
		help_treat_temp2(&t, for_set);
	}
	free(tr->temp);
	free(t.new);
}

void	rm_quotes_redir(t_readed *r)
{
	t_index	ah;
	char	*temp_out;

	init_index(&ah);
	while (ah.a < ct_struct_tb_redir(r->re))
	{
		ah.b = 0;
		while (ah.b < ct_struct_redir(r->re[ah.a]))
		{
			temp_out = process_output(r, &ah);
			if (r->re[ah.a][ah.b].output)
				free(r->re[ah.a][ah.b].output);
			r->re[ah.a][ah.b].output = temp_out;
			ah.b++;
		}
		ah.a++;
	}
}
