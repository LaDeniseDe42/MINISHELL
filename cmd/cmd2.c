/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:44:28 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/10 14:50:42 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp_pipex(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

int	set_double_input(t_readed *r, int cmd_nb, t_index *i, int fd)
{
	fd = open(".heredoc", O_RDONLY);
	if (fd == -1)
	{
		error_on_redir(r, 0, i);
		write(2, "Minishell: Problem with file : ", 32);
		ft_putstr_fd(r->re[cmd_nb][i->a].output, 2);
		write(2, "\n", 1);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	redistri_jobs(t_readed *r, t_index *i, int cmd_nb)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(r->re[cmd_nb][i->a].redir, "<", 2) == 0)
		ret = exec_single_input(r, cmd_nb, i);
	else if (ft_strncmp(r->re[cmd_nb][i->a].redir, ">", 2) == 0)
		ret = exec_single_output(r, cmd_nb, i);
	else if (ft_strncmp(r->re[cmd_nb][i->a].redir, ">>", 3) == 0)
		ret = exec_double_output(r, cmd_nb, i);
	else if (ft_strncmp(r->re[cmd_nb][i->a].redir, "<<", 3) == 0)
		ret = set_double_input(r, cmd_nb, i, 0);
	return (ret);
}

void	ft_exec_this(t_readed *r, int cmd_nbr)
{
	int		base_fds[2];
	int		ret;

	ret = 0;
	base_fds[0] = dup(STDIN_FILENO);
	base_fds[1] = dup(STDOUT_FILENO);
	ret = exec_redir(r, cmd_nbr, &base_fds);
	if ((ret == 0 || ret == 1) && ((count_3_tb(r->new_parsed) == 1
				&& is_empty(r->new_parsed[0][0]) == 0)
		|| (count_3_tb(r->new_parsed) > 1)))
	{
		if (r->new_parsed[cmd_nbr][0]
				&& ft_strchr(r->new_parsed[cmd_nbr][0], '/'))
			exec_slash(r, cmd_nbr);
		else if (check_builtin(r, cmd_nbr) != 1)
			i_am_not_a_normer(r, cmd_nbr);
	}
	if (count_3_tb(r->new_parsed) == 1 && not_fork_for_this(r, cmd_nbr) == 1)
	{
		if (ret == 0)
			reset_fds(base_fds);
	}
	else
		exit(0);
}
