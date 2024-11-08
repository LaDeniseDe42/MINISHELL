/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:32:54 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/06 13:23:21 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_index(t_index *index)
{
	index->a = 0;
	index->b = 0;
	index->c = 0;
	index->i = 0;
	index->j = 0;
}

void	init_pars(t_pars *pars)
{
	pars->parsed = NULL;
	pars->for_set = NULL;
	pars->flag = 0;
	pars->prev_flag = 0;
	init_index(&pars->index);
}

void	init_readed(t_readed *r)
{
	r->its_ok = 0;
	r->parsed = NULL;
	r->readed = NULL;
	r->new_parsed = NULL;
	r->env = NULL;
	r->export = NULL;
	r->flag = 0;
	r->p_flag = 0;
	g_core.err_code = 0;
	r->re = NULL;
}

void	init_correct_path(t_correct_path *cp)
{
	cp->path = NULL;
	cp->all_path = NULL;
	cp->cmd_path = NULL;
	cp->line = 0;
	cp->cmd_slash = NULL;
}

void	init_add_export_struct(t_add_export_to_env *a)
{
	a->i = 0;
	a->j = 0;
	a->k = 0;
	a->flag = 0;
	a->ret = 0;
	a->buff = NULL;
}
