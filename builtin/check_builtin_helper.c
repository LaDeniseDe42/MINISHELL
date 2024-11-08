/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:53:52 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/10 15:17:11 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	help_cd(t_readed *r, char **temp)
{
	cd(temp[1], r, 0);
	return (1);
}

int	help_echo(char **temp, t_readed *r)
{
	my_echo(temp, r);
	return (1);
}

void	help_env(t_readed *r, char **temp)
{
	ft_env(temp, r);
}

void	help_export(t_readed *r, char **temp)
{
	export_my_goat(r, temp);
}

void	help_unset(t_readed *r, char **temp)
{
	unset_my_goat(r, temp);
}
