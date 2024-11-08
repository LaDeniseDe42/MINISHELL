/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:26:47 by akastler          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:35 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verif_after_dol(char *line, int i)
{
	if (((line[i] >= 'A' && line[i] <= 'Z')
			|| (line[i] >= 'a' && line[i] <= 'z')
			|| (line[i] >= '0' && line[i] <= '9')
			|| line[i] == '_'))
		return (1);
	else
		return (0);
}

int	help_search_env(t_readed *mini, char **tb_temp, int i, char *str)
{
	int	len;

	len = ft_strlen(str) + 1;
	while (mini->env[i] && str)
	{
		tb_temp = ft_split(mini->env[i], '=');
		if (ft_strncmp(str, tb_temp[0], len) == 0)
		{
			free_tb(tb_temp);
			break ;
		}
		i++;
		free_tb(tb_temp);
	}
	return (i);
}

int	ft_search_env(char *str, t_readed *mini, int id)
{
	int		i;
	int		len;
	char	**tb_temp;

	i = 0;
	len = ft_strlen(str) + 1;
	if (id == 1)
		return (help_search_env(mini, NULL, i, str));
	else if (id == 2)
	{
		while (mini->export[i] && str)
		{
			tb_temp = ft_split(mini->export[i], '=');
			if (ft_strncmp(str, tb_temp[0], len) == 0)
			{
				free_tb(tb_temp);
				break ;
			}
			i++;
			free_tb(tb_temp);
		}
	}
	return (i);
}

char	*add_str(char *add_this, char *to_this)
{
	int		i;
	char	*new;

	i = 0;
	if (!add_this)
		return (to_this);
	while (add_this[i])
	{
		to_this = add_char(add_this[i], to_this);
		i++;
	}
	free(add_this);
	new = ft_strjoin(to_this, "");
	free(to_this);
	return (new);
}

void	rm_startnend_quotes(char **commands, int i)
{
	char	*new;
	int		j;
	int		k;

	new = ft_calloc(ft_strlen(commands[i]), sizeof(char));
	j = 1;
	k = 0;
	while (commands[i][j])
	{
		if ((commands[i][j] == '\'' || commands[i][j] == '\"')
			&& commands[i][j + 1] == '\0')
			break ;
		new[k++] = commands[i][j];
		j++;
	}
	free(commands[i]);
	commands[i] = new;
}
