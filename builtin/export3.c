/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:11:05 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/06 17:47:35 by qdenizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	modify_one_line(char **old_tb, int search_return, char *temp)
{
	free(old_tb[search_return]);
	old_tb[search_return] = NULL;
	old_tb[search_return] = ft_strjoin(temp, "");
}

void	addback_to_line(char **old_tb, int search_return, char *buff)
{
	char	*temp;
	char	*temp2;

	temp = old_tb[search_return];
	old_tb[search_return][ft_strlen(old_tb[search_return])] = '\0';
	temp2 = ft_strjoin(buff, "");
	old_tb[search_return] = ft_strjoin(old_tb[search_return], temp2);
	free(temp2);
	free(temp);
}

char	*rmquote_again(char *shit)
{
	int		i;
	int		k;
	char	*new;

	new = ft_calloc(ft_strlen(shit) + 1, sizeof(char));
	i = 0;
	k = 0;
	while (shit[i])
	{
		if (shit[i] == '\"' && (shit[i - 1] && shit[i - 1] == '='))
			i++;
		new[k++] = shit[i++];
	}
	return (new);
}
