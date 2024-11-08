/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:03:06 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:35 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(char **temp, t_readed *mini)
{
	(void)temp;
	ft_print_tb(mini->env);
}

void	ft_change_env(char **replace_by, char *this)
{
	int		i;
	int		j;
	int		k;
	char	*s;
	char	*temp;

	i = 0;
	k = 0;
	j = -1;
	if (!*replace_by)
		return ;
	while ((*replace_by)[i] && (*replace_by)[i] != '=')
		i++;
	s = ft_calloc(sizeof(char), i + 2);
	while (++j <= i)
		s[j] = (*replace_by)[j];
	while (this[k] && this[k] != '=')
		k++;
	k++;
	temp = s;
	s = ft_strjoin(s, this + k);
	free(*replace_by);
	*replace_by = s;
	free(temp);
}

void	ft_change_env_sub(char **replace_by, char *this)
{
	char	*s;

	s = this;
	this = ft_strjoin("=", this);
	free(s);
	ft_change_env(replace_by, this);
	free(this);
}
