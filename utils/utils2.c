/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:12:24 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/10 14:53:29 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_nb_commands(char *str, int cmd_nb, int i, int flag)
{
	while (str[i])
	{
		if (str[i] == '\"' && flag == 0)
			flag = 2;
		else if (str[i] == '\"' && flag == 2)
			flag = 0;
		if (str[i] == '\'' && flag == 0)
			flag = 1;
		else if (str[i] == '\'' && flag == 1)
			flag = 0;
		if (str[i] == '|' && flag == 0)
		{
			cmd_nb++;
			while (str[i] == '|')
				i++;
		}
		else
			i++;
	}
	return (cmd_nb + 1);
}

void	flag_state(char *str, int *flag, int i)
{
	if (str[i] == '\"' && *flag == 0)
		*flag = 2;
	else if (str[i] == '\"' && *flag == 2)
		*flag = 0;
	if (str[i] == '\'' && *flag == 0)
		*flag = 1;
	else if (str[i] == '\'' && *flag == 1)
		*flag = 0;
}

char	*add_char(char add_this, char *to_this)
{
	char	*added;
	int		i;

	i = 0;
	added = ft_calloc(ft_strlen(to_this) + 2, sizeof(char));
	while (to_this[i])
	{
		added[i] = to_this[i];
		i++;
	}
	added[i] = add_this;
	free(to_this);
	return (added);
}

int	ft_words(char *s)
{
	int	i;
	int	j;
	int	k;
	int	flag;

	i = 0;
	j = 0;
	k = 0;
	flag = 0;
	while (s[k])
	{
		flag_state(s, &flag, k);
		if (is_space(s[k]) == 0 && j == 0 && flag == 0)
		{
			j = 1;
			i++;
		}
		else if (is_space(s[k]) == 1)
			j = 0;
		k++;
	}
	return (i);
}

void	add_args(char *str, char ***parsed, int pos)
{
	t_index	i;
	char	**tb;
	int		flag;

	flag = 0;
	init_index(&i);
	tb = ft_calloc(ft_words(str) + 1, sizeof(char *));
	while (str[i.i])
	{
		while (str[i.i] && str[i.i] == ' ')
			flag_state(str, &flag, i.i++);
		if (i.j < ft_words(str))
		{
			tb[i.j] = ft_calloc(1, 1);
			while (str[i.i] && char_in_quotes_whitespace(str, i.i, flag) == 1)
			{
				flag_state(str, &flag, i.i);
				tb[i.j] = add_char(str[i.i++], tb[i.j]);
			}
			i.j++;
		}
		while (str[i.i] && is_space(str[i.i]) == 1)
			i.i++;
	}
	parsed[pos] = tb;
}
