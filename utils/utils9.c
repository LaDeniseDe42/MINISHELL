/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:49:53 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:34 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_redirs_tb(t_redir **redir)
{
	t_index	ind;

	init_index(&ind);
	while (redir[ind.a])
	{
		ind.b = 0;
		while (redir[ind.a][ind.b].redir)
		{
			free(redir[ind.a][ind.b].output);
			free(redir[ind.a][ind.b].redir);
			ind.b++;
		}
		free(redir[ind.a]);
		ind.a++;
	}
	free(redir);
}

void	reset_fds(int base_fds[2])
{
	dup2(base_fds[0], STDIN_FILENO);
	close(base_fds[0]);
	dup2(base_fds[1], STDOUT_FILENO);
	close(base_fds[1]);
}

char	*ft_give_path(char **env)
{
	int	line;
	int	i;

	line = 0;
	i = 0;
	while (env[line])
	{
		if (ft_strncmp_pipex("PATH=", env[line], 5) == 0)
		{
			return (env[line]);
		}
		line++;
	}
	return (NULL);
}

char	*help_gcp(t_correct_path *cp)
{
	if (access(cp->cmd_path, F_OK) == -1)
	{
		cp->line++;
		free(cp->cmd_path);
		return (NULL);
	}
	else
	{
		free_tb(cp->all_path);
		return (cp->cmd_path);
	}
}

char	*give_correct_path(char *cmd, char **env)
{
	t_correct_path	cp;
	char			*temp;

	if (cmd)
	{
		init_correct_path(&cp);
		cp.path = ft_give_path(env);
		if (!cp.path || ft_strlen(cmd) == 0)
			return (NULL);
		cp.all_path = ft_split(cp.path + 5, ':');
		while (cp.all_path[cp.line])
		{
			cp.cmd_slash = ft_strjoin("/", cmd);
			cp.cmd_path = ft_strjoin(cp.all_path[cp.line], cp.cmd_slash);
			free(cp.cmd_slash);
			temp = help_gcp(&cp);
			if (temp != NULL)
				return (temp);
		}
		free_tb(cp.all_path);
	}
	return (NULL);
}
