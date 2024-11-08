/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:15:14 by akastler          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:36 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	help_pipe(t_pipe *p)
{
	if (pipe(p->pipe_fd) == -1)
	{
		perror("pipe error\n");
		return ;
	}
	p->pids[p->i] = fork();
	if (p->child_pid == -1)
	{
		perror("fork error\n");
		return ;
	}
}

void	help_pipe_2(t_pipe *p, t_readed *r)
{
	if (p->pids[p->i] == 0)
	{
		close(p->pipe_fd[0]);
		if (p->i > 0)
		{
			dup2(p->prev_pipe_read, STDIN_FILENO);
			close(p->prev_pipe_read);
		}
		if (p->i < p->nb_cmd - 1)
			dup2(p->pipe_fd[1], STDOUT_FILENO);
		ft_exec_this(r, p->i);
		exit (0);
	}
	else
	{
		close(p->pipe_fd[1]);
		if (p->i > 0)
			close(p->prev_pipe_read);
		p->prev_pipe_read = p->pipe_fd[0];
	}
}

void	do_the_pipe(t_readed *r)
{
	t_pipe	p;
	int		temp;
	int		ret_val;

	init_pipe_struct(&p);
	temp = 0;
	ret_val = 0;
	p.nb_cmd = count_3_tb(r->new_parsed);
	p.pids = ft_calloc(p.nb_cmd + 1, sizeof(pid_t));
	while (++p.i < p.nb_cmd)
	{
		help_pipe(&p);
		help_pipe_2(&p, r);
	}
	close(p.prev_pipe_read);
	p.i = -1;
	while (++p.i < p.nb_cmd)
	{
		waitpid(p.pids[p.i], &ret_val, 0);
		g_core.err_code = WEXITSTATUS(ret_val);
		temp = 1;
	}
	free(p.pids);
}
