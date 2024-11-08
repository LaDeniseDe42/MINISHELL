/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:11:06 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:36 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	process_redir(t_readed *r, char *for_parse, t_pars *pars)
{
	char	*redir;
	char	c;
	t_redir	oh;

	(void)r;
	(void)pars;
	oh.output = NULL;
	oh.redir = NULL;
	redir = ft_calloc(1, 1);
	c = for_parse[pars->index.i];
	while (for_parse[pars->index.i] && for_parse[pars->index.i] == c)
		redir = add_char(for_parse[pars->index.i++], redir);
	if (ft_strlen(redir) > 2)
		printf("Error\n");
	return (oh);
}

int	verif_triple_or_more(char *arg)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (arg[i])
	{
		flag_state(arg, &flag, i);
		if ((arg[i] == '>' || arg[i] == '<') && flag == 0)
			return (1);
		i++;
	}
	return (0);
}

int	found_redir(char **line)
{
	t_un_chevron	c;
	int				i;
	int				tot;

	i = 0;
	tot = 0;
	while (line[i])
	{
		init_t_un_chevron(&c);
		ad_redir(line[i], &c);
		c.total = c.d_d + c.d_g + c.s_d + c.s_g;
		if (c.total == 0)
		{
			if (verif_triple_or_more(line[i]) == 1)
				return (-1);
		}
		tot += c.total;
		i++;
	}
	return (tot);
}

int	redir_pars(t_readed *r, int ret)
{
	t_pars	pars;

	init_pars(&pars);
	pars.parsed = ft_calloc(count_3_tb(r->parsed) + 1, sizeof(char **));
	r->re = ft_calloc(count_3_tb(r->parsed) + 1, sizeof(t_redir *));
	while (r->parsed[pars.index.i])
	{
		ret = found_redir(r->parsed[pars.index.i]);
		pars.index.c = 0;
		r->re[pars.index.i] = ft_calloc(ret + 1, sizeof(t_redir));
		if (ret == -1)
		{
			free_3d_tb(r->parsed);
			return (-1);
		}
		else if (ret == 0)
			pars.parsed[pars.index.i] = ft_copy_tb(r->parsed[pars.index.i]);
		else
			treat_redir(r->parsed[pars.index.i], r, &pars);
		pars.index.i++;
	}
	free_3d_tb(r->parsed);
	r->parsed = pars.parsed;
	return (0);
}

int	ft_count_redir(char *s)
{
	int	i;
	int	j;
	int	k;
	int	flag;

	i = 0;
	j = 0;
	k = 0;
	flag = 0;
	while (s[k])
	{
		flag_state(s, &flag, k);
		if (s[k] != ' ' && j == 0 && flag == 0)
		{
			j = 1;
			i++;
		}
		else if (s[k] == ' ')
			j = 0;
		k++;
	}
	return (i);
}
