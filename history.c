/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:32:23 by qdenizar          #+#    #+#             */
/*   Updated: 2023/07/04 16:35:24 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	recover_history(void)
{
	char	*str;

	if (g_core.history_fd > 0)
	{
		str = get_next_line(g_core.history_fd);
		while (str && ft_strlen(str) > 0)
		{
			if (str[ft_strlen(str) - 1] == '\n')
				str[ft_strlen(str) - 1] = '\0';
			add_history(str);
			free(str);
			str = get_next_line(g_core.history_fd);
		}
		close(g_core.history_fd);
	}
	g_core.history_fd = open(".history", O_RDWR | O_APPEND | O_CREAT, 0644);
}

void	history(char *line)
{
	char	*str;

	if (g_core.history_fd > 0)
	{
		add_history(line);
		str = ft_strjoin(line, "\n");
		ft_putstr_fd(str, g_core.history_fd);
		free(str);
	}
}
