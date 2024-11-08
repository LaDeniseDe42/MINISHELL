/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:02:00 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:35 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sub_cd(char *path, t_readed *mini)
{
	int		line;
	char	*new_path;
	int		ret_val;

	line = 0;
	ret_val = 0;
	if (path[0] == '~' && path[1] == '/')
	{
		line = ft_search_env("HOME", mini, 1);
		new_path = ft_strjoin(mini->env[line] + 5, path + 1);
		ret_val = chdir(new_path);
		free(new_path);
	}
	else
		ret_val = chdir(path);
	if (ret_val == -1)
		ret_val += 2;
	return (ret_val);
}

void	modif_cd(t_readed *mini, char **pwds)
{
	char	*temp[2];

	temp[0] = ft_strjoin("OLDPWD=", pwds[0]);
	temp[1] = ft_strjoin("PWD=", pwds[1]);
	treat_equal(mini, temp[0]);
	treat_equal(mini, temp[1]);
	free(temp[0]);
	free(temp[1]);
	mini->export = ft_sort_tb_alpha(mini->export);
}

void	cd(char *path, t_readed *mini, int flag)
{
	int		pwd;
	int		old_pwd;
	char	*pwds[2];

	g_core.err_code = 0;
	pwd = ft_search_env("PWD", mini, 1);
	old_pwd = ft_search_env("OLDPWD", mini, 1);
	pwds[0] = getcwd(NULL, 4096);
	if (!path || ft_strncmp("~", path, 2) == 0)
		g_core.err_code = chdir(mini->env[ft_search_env("HOME", mini, 1)] + 5);
	else if (ft_strncmp(path, "-", 2) == 0)
	{
		if (old_pwd < ft_count_tb(mini->env)
			&& ft_strlen(mini->env[old_pwd]) - 7 > 0)
			g_core.err_code = chdir(mini->env[old_pwd] + 7);
		else
		{
			g_core.err_code = 1;
			flag = 1;
			ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2);
		}
	}
	else
		g_core.err_code = sub_cd(path, mini);
	reduce_cd(mini, pwds, flag);
}

void	reduce_cd(t_readed *mini, char **pwds, int flag)
{
	pwds[1] = getcwd(NULL, 4096);
	if (g_core.err_code == 0)
	{
		modif_cd(mini, pwds);
		free(pwds[0]);
		free(pwds[1]);
	}
	else if (flag == 0)
	{
		free(pwds[0]);
		free(pwds[1]);
		perror("Minishell: cd");
	}
}
