/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:53:04 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:34 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_ttt(t_tt *t)
{
	t->i = 0;
	t->c = 0;
	t->pirate_flag = 0;
	t->new = NULL;
}

void	init_treat_redir(t_treat_redir *tr, char **tb)
{
	tr->i = -1;
	tr->z = -1;
	tr->flag = 0;
	tr->temp = NULL;
	tr->tb_cpy = ft_copy_tb(tb);
}

void	init_pipe_struct(t_pipe *p)
{
	p->child_pid = 0;
	p->i = -1;
	p->nb_cmd = 0;
	p->prev_pipe_read = 0;
}

void	init_t_un_chevron(t_un_chevron *c)
{
	c->d_d = 0;
	c->d_g = 0;
	c->s_d = 0;
	c->s_g = 0;
	c->total = 0;
}
