/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:07:17 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/10 14:56:04 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handle(int signum)
{
	(void)signum;
	if (g_core.in_exec == 0)
	{
		if (!(waitpid(-1, NULL, WNOHANG) > 0))
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_core.err_code = 1;
		}
	}
	else if (g_core.in_exec == 1)
	{
		if ((waitpid(-1, NULL, WNOHANG) > 0))
		{
			printf("\n");
			g_core.err_code = 130;
		}
	}
}

void	sigquit_handle(int signum)
{
	(void)signum;
	if (g_core.in_exec == 1)
	{
		g_core.err_code = 131;
	}
}

void	what_signals(void)
{
	signal(SIGINT, sigint_handle);
	signal(SIGQUIT, sigquit_handle);
}

void	fonction_nulle(int sign)
{
	(void)sign;
}
