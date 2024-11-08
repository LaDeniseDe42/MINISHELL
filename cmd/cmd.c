/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:44:10 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/10 11:51:12 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_handler(t_readed *r, char *cmd, int error_code)
{
	(void)r;
	if (error_code == 127)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (error_code == 126)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	exit(error_code);
}

int	not_fork_for_this(t_readed *r, int cmd_nb)
{
	if (ft_count_tb(r->new_parsed[cmd_nb]) == 0
		|| ft_strlen(r->new_parsed[cmd_nb][0]) == 0)
		return (0);
	if (ft_strncmp(r->new_parsed[cmd_nb][0], "cd", 3) == 0
		|| ft_strncmp(r->new_parsed[cmd_nb][0], "export", 7) == 0
		|| ft_strncmp(r->new_parsed[cmd_nb][0], "unset", 6) == 0
		|| ft_strncmp(r->new_parsed[cmd_nb][0], "exit", 5) == 0)
		return (1);
	else
		return (0);
}

void	try_this_command(t_readed *r)
{
	if (count_3_tb(r->new_parsed) >= 1)
	{
		if (count_3_tb(r->new_parsed) == 1)
		{
			if (not_fork_for_this(r, 0) == 0)
				exec_solo(r);
			else
				ft_exec_this(r, 0);
		}
		else
			do_the_pipe(r);
	}
}

void	exec_solo(t_readed *r)
{
	pid_t	son;
	int		status;

	son = fork();
	status = 0;
	if (son == -1)
		printf("ERROR FORK FAILED\n");
	else if (son == 0)
		ft_exec_this(r, 0);
	else
	{
		waitpid(son, &status, 0);
		g_core.err_code = WEXITSTATUS(status);
	}
}

void	exec_slash(t_readed *r, int cmd_nb)
{
	execve(r->new_parsed[cmd_nb][0], r->new_parsed[cmd_nb], r->env);
	if (access(r->new_parsed[cmd_nb][0], F_OK) == -1)
		error_handler(r, r->new_parsed[cmd_nb][0], 127);
	else
		error_handler(r, r->new_parsed[cmd_nb][0], 126);
}
