/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:03:25 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/10 14:05:53 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_single_input(t_readed *r, int cmd_nb, t_index *i)
{
	int	fd;

	fd = open(r->re[cmd_nb][i->a].output, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Minishell: Problem with file: ", 31);
		ft_putstr_fd(r->re[cmd_nb][i->a].output, 2);
		write(2, "\n", 1);
		error_on_redir(r, cmd_nb, i);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	exec_single_output(t_readed *r, int cmd_nb, t_index *i)
{
	int	fd;

	fd = open(r->re[cmd_nb][i->a].output, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, "Minishell: Problem with file: ", 31);
		ft_putstr_fd(r->re[cmd_nb][i->a].output, 2);
		write(2, "\n", 1);
		error_on_redir(r, 0, i);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	exec_double_output(t_readed *r, int cmd_nb, t_index *i)
{
	int	fd;

	fd = open(r->re[cmd_nb][i->a].output, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		write(2, "Minishell: Problem with file: ", 31);
		ft_putstr_fd(r->re[cmd_nb][i->a].output, 2);
		write(2, "\n", 1);
		error_on_redir(r, cmd_nb, i);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

void	while_of_heredoc(t_readed *r, int cmd_nb, t_index *i, int fd)
{
	char	*input_str;

	while (1)
	{
		input_str = readline("heredoc > ");
		if (input_str)
		{
			if (ft_strncmp(input_str, r->re[cmd_nb][i->a].output,
				ft_strlen(r->re[cmd_nb][i->a].output) + 1) == 0)
				break ;
			parsing_heredoc(input_str, fd, r);
			free(input_str);
		}
		else
			exit(0);
	}
	exit(0);
}

int	exec_double_input(t_readed *r, int cmd_nb, t_index *i, int fd)
{
	pid_t	child;

	fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		mini_help_error(r, i, cmd_nb);
		error_on_redir(r, cmd_nb, i);
		return (-1);
	}
	signal(SIGINT, SIG_DFL);
	child = fork();
	if (child == -1)
		return (-1);
	if (child == 0)
		while_of_heredoc(r, cmd_nb, i, fd);
	else
		waitpid(child, NULL, 0);
	close(fd);
	return (0);
}
