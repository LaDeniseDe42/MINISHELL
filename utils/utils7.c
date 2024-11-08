/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:23:28 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/10 12:02:15 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	between_char(char *nathan, int guillaume, char adrien)
{
	int	axel;
	int	quentin;

	axel = guillaume;
	quentin = 0;
	while (nathan[axel] && nathan[axel] != adrien)
		axel--;
	if (nathan[axel] == adrien)
		quentin++;
	axel = guillaume;
	while (nathan[axel] && nathan[axel] != adrien)
		axel++;
	if (nathan[axel] == adrien)
		quentin++;
	return (quentin);
}

char	*rm_startnend_quotes_solo(char *command)
{
	char	*new;
	int		j;
	int		k;

	new = ft_calloc(ft_strlen(command), sizeof(char));
	j = 1;
	k = 0;
	while (command[j])
	{
		if ((command[j] == '\'' || command[j] == '\"')
			&& command[j + 1] == '\0')
			break ;
		new[k++] = command[j];
		j++;
	}
	return (new);
}

int	check_3d_null(char ***tb, t_readed *r)
{
	int	i;

	i = 0;
	(void)r;
	while (tb[i])
	{
		if (tb[i][0] == NULL)
		{
			if (!r->re[i][0].redir
				|| (r->re[i][0].redir && ft_strlen(r->re[i][0].redir) == 0))
				return (0);
		}
		i++;
	}
	return (1);
}

int	is_empty(char *str)
{
	int	i;

	i = 0;
	if (!str || ft_strlen(str) == 0)
		return (1);
	while (str[i])
	{
		if (str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13))
			return (0);
		i++;
	}
	return (1);
}

void	dol_error(t_readed *r, t_index *i, int id)
{
	char	*code;

	code = ft_itoa(g_core.err_code);
	i->c++;
	if (id == 1)
		r->new_parsed[i->a][i->b] = add_str(code, r->new_parsed[i->a][i->b]);
}
