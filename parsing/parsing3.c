/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:43:40 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:35 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	anything_after_redir(char *str, int i)
{
	char	c;
	int		after;

	c = str[i];
	after = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		after++;
		i++;
	}
	if (after > 0)
		return (1);
	return (0);
}

void	treat_redir(char **tb, t_readed *r, t_pars *pars)
{
	t_treat_redir	tr;
	int				oh_merde;
	t_tt			t;

	init_ttt(&t);
	oh_merde = 0;
	init_treat_redir(&tr, tb);
	oh_merde = ft_count_tb(tr.tb_cpy);
	while (++tr.i < oh_merde)
	{
		tr.flag = 0;
		tr.z = -1;
		while (tr.tb_cpy[tr.i][++tr.z])
		{
			flag_state(tr.tb_cpy[tr.i], &tr.flag, tr.z);
			if ((tr.tb_cpy[tr.i][tr.z] == '>'
				|| tr.tb_cpy[tr.i][tr.z] == '<') && tr.flag == 0)
			{
				treat_temp(r, pars, &tr, &t);
				break ;
			}
		}
	}
	pars->parsed[pars->index.i] = tr.tb_cpy;
}

void	print_redir_tb(t_redir **re)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (re[i])
	{
		j = 0;
		while (re[i][j].redir)
		{
			printf("struct[%d][%d]\nredir = [%s] | output = [%s]\n", i, j,
				re[i][j].redir, re[i][j].output);
			j++;
		}
		i++;
	}
}

void	reduce_ad_redir(char *tb, int *j, t_un_chevron *c, int flag)
{
	int	count;

	count = 0;
	if (tb[*j] && tb[*j] == '<' && flag == 0)
	{
		while (tb[*j] == '<')
		{
			count++;
			*j += 1;
		}
		if (count <= 2)
			c->d_d++;
	}
	else if (tb[*j] && tb[*j] == '>' && flag == 0)
	{
		while (tb[*j] == '>')
		{
			count++;
			*j += 1;
		}
		if (count <= 2)
			c->d_d++;
	}
}

void	ad_redir(char *tb, t_un_chevron *c)
{
	int	j;
	int	flag;

	j = -1;
	flag = 0;
	if (!tb)
		return ;
	while (tb[++j])
	{
		flag_state(tb, &flag, j);
		reduce_ad_redir(tb, &j, c, flag);
		if (j >= (int)ft_strlen(tb))
			break ;
	}
}
