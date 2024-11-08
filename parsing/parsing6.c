/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:47:06 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:35 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_char_redir2(t_readed *r, t_index *i, char **temp_out)
{
	if (r->re[i->a][i->b].output[i->c] == '\"'
		&& (r->flag == 2 || r->p_flag == 2))
		;
	else if (r->re[i->a][i->b].output[i->c] == '\''
		&& (r->flag == 1 || r->p_flag == 1))
		;
	else
		*temp_out
			= add_char(r->re[i->a][i->b].output[i->c], *temp_out);
}

void	dol_error_redir(t_readed *r, char **temp_out, t_index *ah)
{
	char	*code;

	(void)r;
	code = ft_itoa(g_core.err_code);
	*temp_out = add_str(code, *temp_out);
	ah->c++;
}

void	process_char_redir(t_readed *r, t_index *ah, int ret, char **temp_out)
{
	char	*search;

	if (r->re[ah->a][ah->b].output[ah->c] == '$' && r->flag != 1)
	{
		if (r->re[ah->a][ah->b].output[++ah->c] == '?')
			dol_error_redir(r, temp_out, ah);
		else if (verif_after_dol(r->re[ah->a][ah->b].output, ah->c) == 1)
		{
			search = ft_calloc(1, 1);
			while (verif_after_dol(r->re[ah->a][ah->b].output, ah->c))
				search = add_char(r->re[ah->a][ah->b].output[ah->c++], search);
			ret = ft_search_env(search, r, 2);
			if (ret < ft_count_tb(r->export) && r->export[ret])
				*temp_out
					= add_str(ft_strjoin(r->export[ret]
							+ (ft_strlen(search) + 1), ""),
						*temp_out);
			free(search);
		}
		else
			*temp_out = add_char('$', *temp_out);
		ah->c--;
	}
	else
		process_char_redir2(r, ah, temp_out);
}

char	*process_output(t_readed *r, t_index *ah)
{
	char	*temp_out;

	ah->c = 0;
	r->flag = 0;
	if (!r->re[ah->a][ah->b].output
		|| ft_strlen(r->re[ah->a][ah->b].output) == 0)
		return (NULL);
	temp_out = ft_calloc(1, 1);
	while (r->re[ah->a][ah->b].output[ah->c])
	{
		r->p_flag = r->flag;
		flag_state(r->re[ah->a][ah->b].output, &r->flag, ah->c);
		process_char_redir(r, ah, 0, &temp_out);
		ah->c++;
	}
	return (temp_out);
}
