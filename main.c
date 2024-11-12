/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 08:19:58 by akastler          #+#    #+#             */
/*   Updated: 2023/07/10 15:59:30 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_core	g_core;

int	main(int argc, char **argv, char **env)
{
	t_readed	r;

	start_minishell(&r, env, argc, argv);
	while (1)
	{
		g_core.in_exec = 0;
		tcsetattr(r.term, 0, &r.attr);
		r.readed = readline(MINIGOAT" Minichevre >> ");
		if (r.readed)
		{
			if (continue_or_not(&r) == -1)
				continue ;
			process(&r);
		}
		else
		{
			printf("\033[1A\033[15Cexit\n");
			if (g_core.history_fd)
				close(g_core.history_fd);
			exit(1);
		}
	}
}

void	start_minishell(t_readed *r, char **env, int argc, char **argv)
{
	if (argc != 1)
	{
		printf("Minichevre: Too many arguments\n");
		exit(1);
	}
	(void)argv;
	init_readed(r);
	printf("\e[32m%s\n\e[0m", GOAT);
	r->env = ft_copy_tb(env);
	shlvl(r);
	r->export = ft_sort_tb_alpha(ft_copy_tb(r->env));
	check_old_pwd(r);
	what_signals();
	rl_catch_signals = 0;
	g_core.in_exec = 0;
	g_core.history_fd = open(".history", O_RDONLY);
	recover_history();
	r->term = dup(STDIN_FILENO);
	tcgetattr(r->term, &r->attr);
}
