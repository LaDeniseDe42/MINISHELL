/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:40:34 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/10 11:51:45 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_while_exec_redir(t_readed *r, int cmd_nb)
{
	int		ret;
	t_index	i;

	ret = 0;
	init_index(&i);
	while (r->re[cmd_nb][i.a].redir)
	{
		ret = 0;
		if (ft_strlen(r->re[cmd_nb][i.a].redir) > 0 && ret == 0
			&& ft_strncmp(r->re[cmd_nb][i.a].redir, "<<", 3) == 0)
			ret = exec_double_input(r, cmd_nb, &i, 0);
		if (ret == -1)
			break ;
		i.a++;
	}
}

int	exec_redir(t_readed *r, int cmd_nb, int (*base_fds)[2])
{
	t_index	i;
	int		ret;

	init_index(&i);
	ret = 1;
	(void)base_fds;
	if (ct_struct_redir(r->re[cmd_nb]) == 0)
		return (0);
	first_while_exec_redir(r, cmd_nb);
	while (r->re[cmd_nb][i.a].redir)
	{
		ret = 0;
		if (ft_strlen(r->re[cmd_nb][i.a].redir) > 0 && ret == 0)
			ret = redistri_jobs(r, &i, cmd_nb);
		if (ret == -1)
			break ;
		i.a++;
	}
	return (ret);
}

void	i_am_not_a_normer(t_readed *r, int cmd_nbr)
{
	char	*correct_path;

	correct_path = give_correct_path(r->new_parsed[cmd_nbr][0], r->env);
	if (!correct_path)
		error_handler(r, r->new_parsed[cmd_nbr][0], 127);
	execve(correct_path, r->new_parsed[cmd_nbr], r->env);
	free(correct_path);
	error_handler(r, r->new_parsed[cmd_nbr][0], 126);
}
