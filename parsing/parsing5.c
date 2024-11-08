/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:01:39 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:35 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	reduce_else_of_if(t_redir *for_set, t_readed *r,
	t_pars *pars, t_treat_redir *tr)
{
	for_set->redir = ft_strjoin(tr->temp, "");
	for_set->output = ft_calloc(1, 1);
	r->re[pars->index.i][pars->index.c] = *for_set;
	return (0);
}

int	treat_temp(t_readed *r, t_pars *pars, t_treat_redir *tr, t_tt *t)
{
	t_redir	for_set;

	shit_bag(tr, &for_set);
	if (anything_after_redir(tr->temp, t->i) == 0)
	{
		if (tr->tb_cpy[tr->i + 1])
		{
			t->new = ft_strjoin(tr->temp, "");
			if (tr->tb_cpy[tr->i + 1][0] == '>'
				|| tr->tb_cpy[tr->i + 1][0] == '<')
				return (reduce_treat_temp(pars, &for_set, r, t));
			else
				reduce_treat_temp3(tr, t);
		}
		else
			return (reduce_else_of_if(&for_set, r, pars, tr));
		while_treat_temp(pars, t, &for_set, r);
		free(t->new);
		free(tr->temp);
	}
	else
		while_treat_temp2(pars, tr, &for_set, r);
	return (0);
}

int	reduce_treat_temp(t_pars *pars, t_redir *for_set, t_readed *r, t_tt *t)
{
	for_set->redir = add_str(ft_strjoin(t->new, ""), for_set->redir);
	for_set->output = ft_calloc(1, 1);
	r->re[pars->index.i][pars->index.c] = *for_set;
	pars->index.c++;
	free(t->new);
	return (0);
}

void	reduce_treat_temp2(t_treat_redir *tr, t_redir *for_set, t_tt *t)
{
	t->new = ft_strjoin(tr->tb_cpy[tr->i + 1], "");
	for_set->redir = ft_calloc(1, 1);
	for_set->output = ft_calloc(1, 1);
	tr->tb_cpy[tr->i + 1][0] = '\0';
}

void	reduce_treat_temp3(t_treat_redir *tr, t_tt *t)
{
	int	w;

	w = 2;
	free(t->new);
	t->new = ft_strjoin(tr->temp, tr->tb_cpy[tr->i + 1]);
	if (t->new[ft_strlen(t->new) - 1] == '<'
		|| t->new[ft_strlen(t->new) - 1] == '>')
	{
		while (anything_after_redir(t->new, ft_strlen(t->new)) == 0)
		{
			if (tr->tb_cpy[tr->i + w])
			{
				t->new = ft_strjoin(t->new, tr->tb_cpy[tr->i + w]);
				tr->tb_cpy[tr->i + w][0] = '\0';
				w++;
			}
			else
				break ;
		}
	}
	tr->tb_cpy[tr->i + 1][0] = '\0';
}
