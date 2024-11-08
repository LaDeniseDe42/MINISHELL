/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:24:46 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:34 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	help_parsing_heredoc(char *str, t_index *i, t_readed *r, char **new)
{
	char	*search;

	search = ft_calloc(1, 1);
	while (verif_after_dol(str, i->i))
		search = add_char(str[i->i++], search);
	i->i--;
	i->c = ft_search_env(search, r, 2);
	if (i->c < ft_count_tb(r->export) && r->export[i->c])
	{
		*new = add_str(ft_strjoin(r->export[i->c]
					+ ft_strlen(search) + 1, ""), *new);
	}
	free(search);
}

void	parsing_heredoc(char *str, int fd, t_readed *r)
{
	char	*new;
	t_index	i;

	new = ft_calloc(1, 1);
	init_index(&i);
	while (str[i.i])
	{
		if (str[i.i] == '$')
		{
			i.i++;
			if (str[i.i] == '?')
				new = add_str(ft_itoa(g_core.err_code), new);
			else
				help_parsing_heredoc(str, &i, r, &new);
		}
		else
			new = add_char(str[i.i], new);
		i.i++;
	}
	write(fd, new, ft_strlen(new));
	write(fd, "\n", 1);
	free(new);
}
