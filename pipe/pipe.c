/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:01:46 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/06 14:11:31 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	help_verif_pipe(char *new, t_readed *r)
{
	char	*temp;

	if (ft_start_with_pipe(new) == 1 || ft_flux(new) == 1)
	{
		ft_putstr_fd("Minichevre: syntax error near unexpected token `|'\n", 2);
		r->its_ok = -1;
	}
	temp = r->readed;
	r->readed = ft_strjoin(r->readed, new);
	free(temp);
	free(new);
}

int	ft_verif_pipe(t_readed *r)
{
	char	*new;

	if (ft_start_with_pipe(r->readed) == 1 || ft_flux(r->readed) == 1)
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `|'\n", 2);
		return (r->its_ok = -1);
	}
	else
	{
		if (ft_end_with_pipe(r->readed) == 1)
		{
			while (1)
			{
				new = readline("Goat Master say => ");
				if (new && ft_strlen(new) > 0
					&& ft_end_with_pipe(r->readed) != 0)
				{
					help_verif_pipe(new, r);
					if (ft_end_with_pipe(r->readed) == 0)
						break ;
				}
			}
		}
	}
	return (r->its_ok = 1);
}

int	ft_start_with_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
	{
		i++;
	}
	if (str[i] == '|')
		return (1);
	return (0);
}

int	ft_end_with_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
	{
		i--;
	}
	if (str[i] == '|')
		return (1);
	return (0);
}

int	ft_flux(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		flag_state(str, &flag, i);
		if ((str[i] == '|' && str[i + 1] == '|') && flag == 0)
			return (1);
		i++;
	}
	return (0);
}
