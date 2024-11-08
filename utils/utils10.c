/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:20:59 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:34 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_old_pwd(t_readed *r)
{
	int	search;

	search = ft_search_env("OLDPWD", r, 2);
	if (search == ft_count_tb(r->export))
	{
		r->export = add_one_line(r->export, "OLDPWD");
		ft_sort_tb_alpha(r->export);
	}
}

void	mini_help_error(t_readed *r, t_index *i, int cmd_nb)
{
	write(2, "Minishell: Problem with HEREDOC : ", 35);
	ft_putstr_fd(r->re[cmd_nb][i->a].output, 2);
	write(2, "\n", 1);
}

void	reduce_help_exit(void)
{
	g_core.err_code = 1;
	ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
}

void	error_on_redir(t_readed *r, int cmd_nb, t_index *i)
{
	(void)i;
	if (count_3_tb(r->new_parsed) == 1)
	{
		if (not_fork_for_this(r, cmd_nb) == 0)
			exit (1);
		else
			g_core.err_code = 1;
	}
	else
		exit (1);
}

void	shlvl(t_readed *r)
{
	int		actual_sh;
	char	*temp;
	char	*new_sh;
	int		i;
	int		sh_line;

	actual_sh = 0;
	i = 0;
	sh_line = ft_search_env("SHLVL", r, 1);
	if (r->env[sh_line])
	{
		while (r->env[sh_line][i] && r->env[sh_line][i] != '=')
			i++;
		i++;
		actual_sh = ft_atoi(r->env[sh_line] + i);
		actual_sh++;
		r->env[sh_line][i] = '\0';
		temp = r->env[sh_line];
		new_sh = ft_itoa(actual_sh);
		r->env[sh_line] = ft_strjoin(r->env[sh_line], new_sh);
		free(temp);
		free(new_sh);
	}
	else
		r->env = add_one_line(r->env, "SHLVL=1");
}
