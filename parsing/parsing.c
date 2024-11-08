/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:11:03 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/10 12:58:39 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	***parsing(char *for_parse)
{
	t_pars	pars;

	init_pars(&pars);
	pars.parsed = ft_calloc(find_nb_commands(for_parse, 0, 0, 0)
			+ 1, sizeof(char **));
	while (for_parse[pars.index.i])
	{
		pars.for_set = ft_calloc(1, 1);
		while (for_parse[pars.index.i]
			&& char_in_quotes(for_parse, pars.index.i, pars.flag, '|') == 1)
		{
			flag_state(for_parse, &pars.flag, pars.index.i);
			pars.for_set = add_char(for_parse[pars.index.i++], pars.for_set);
		}
		add_args(pars.for_set, pars.parsed, pars.index.a);
		free(pars.for_set);
		if (for_parse[pars.index.i] == '|'
			&& char_in_quotes(for_parse, pars.index.i, pars.flag, '|') == 0)
		{
			pars.index.a++;
			while (for_parse[pars.index.i] == '|')
				pars.index.i++;
		}
	}
	return (pars.parsed);
}

void	process_char2(t_readed *r, t_index *i)
{
	if (r->parsed[i->a][i->b][i->c] == '\"'
		&& (r->flag == 2 || r->p_flag == 2))
		;
	else if (r->parsed[i->a][i->b][i->c] == '\''
		&& (r->flag == 1 || r->p_flag == 1))
		;
	else
		r->new_parsed[i->a][i->b]
			= add_char(r->parsed[i->a][i->b][i->c], r->new_parsed[i->a][i->b]);
}

void	parsing_part2(t_readed *r)
{
	t_index	i;

	init_index(&i);
	r->new_parsed = ft_calloc(count_3_tb(r->parsed) + 1, sizeof(char **));
	while (i.a < count_3_tb(r->parsed))
	{
		r->new_parsed[i.a]
			= ft_calloc(ft_count_tb(r->parsed[i.a]) + 1, sizeof(char *));
		i.b = 0;
		while (i.b < ft_count_tb(r->parsed[i.a]))
		{
			i.c = 0;
			r->new_parsed[i.a][i.b] = ft_calloc(1, 1);
			while (r->parsed[i.a][i.b][i.c])
			{
				r->p_flag = r->flag;
				flag_state(r->parsed[i.a][i.b], &r->flag, i.c);
				process_char2(r, &i);
				i.c++;
			}
			i.b++;
		}
		i.a++;
	}
}
