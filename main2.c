/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:46:56 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/10 15:57:37 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_redir(t_readed *r)
{
	t_index	i;

	init_index(&i);
	while (r->re[i.a])
	{
		i.b = 0;
		while (r->re[i.a][i.b].redir)
		{
			if (ft_strlen(r->re[i.a][i.b].output) == 0)
			{
				printf("Minichevre: the goat noticed that one of the\
 redirections was missing an output\n");
				return (-1);
			}
			i.b++;
		}
		i.a++;
	}
	return (0);
}

void	p(t_readed *r)
{
	realign_tb_if_needed(r);
	parsing_part2(r);
}

void	minigoat_process_on_fire(t_readed *r)
{
	char	*temp;

	r->parsed = parsing(r->readed);
	if (redir_pars(r, 0) == -1)
	{
		printf("MINICHEVRE syntax error near unexpected token `>' or `<'\n");
		return ;
	}
	realign_tb_if_needed(r);
	if (valid_redir(r) == -1)
		return ;
	rm_quotes_redir(r);
	temp = ft_strjoin(r->parsed[0][0], "");
	p(r);
	free_3d_tb(r->parsed);
	if (check_3d_null(r->new_parsed, r) == 1)
		try_this_command(r);
	else
	{
		if (ft_strlen(temp) == 0)
			printf("Minishell: syntax error near unexpected token `|'\n");
	}
	free(temp);
	free_redirs_tb(r->re);
	free_3d_tb(r->new_parsed);
}

void	process(t_readed *r)
{
	if (ft_strlen(r->readed) > 0)
	{
		history(r->readed);
		if (is_empty(r->readed) == 1)
			return ;
		g_core.in_exec = 1;
		if (count_quotes(r->readed) == 1)
		{
			parsing_dollar(r);
			if (ft_strlen(r->readed) > 0)
				minigoat_process_on_fire(r);
		}
		else
			printf("there are unclosed quotes in this line :\n%s\n", r->readed);
		free(r->readed);
		g_core.in_exec = 0;
	}
}

int	continue_or_not(t_readed *r)
{
	if (ft_strchr(r->readed, '|'))
	{
		history(r->readed);
		if (ft_verif_pipe(r) == -1)
			free(r->readed);
		if (r->its_ok == -1)
			return (-1);
	}
	return (0);
}
