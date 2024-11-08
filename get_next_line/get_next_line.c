/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akastler <akastler@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:56:52 by akastler          #+#    #+#             */
/*   Updated: 2023/02/24 14:14:04 by akastler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **s)
{
	free(*s);
	*s = 0;
	return (*s);
}

static char	*ft_getline(char *stock, char *line)
{
	int		i;

	i = 0;
	if (!stock[i])
		return (NULL);
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
		i--;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (stock[i] && stock[i] != '\n')
	{
		line[i] = stock[i];
		i++;
	}
	if (stock[i] == '\n')
	{
		line[i] = stock[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_getnext(char *stock)
{
	int		i;
	int		len;
	char	*newstock;

	i = 0;
	len = 0;
	if (!stock[i])
		return (NULL);
	while (stock[i] && stock[i] != '\n')
		i++;
	newstock = malloc((ft_strlen_gnl(stock) - i + 1) * sizeof(char));
	if (!newstock)
		return (ft_free(&stock));
	if (stock[i] == '\n')
		i++;
	while (stock[i])
		newstock[len++] = stock[i++];
	newstock[len] = '\0';
	free(stock);
	return (newstock);
}

static char	*ft_read(int fd, char *stock)
{
	int		i;
	char	*buff;

	i = 1;
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (ft_free(&stock));
	while (ft_strchr_gnl(stock, '\n') == 0 && i > 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[i] = 0;
		stock = ft_strjoin_gnl(stock, buff);
	}
	free(buff);
	return (stock);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stock;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (ft_free(&stock));
	line = 0;
	stock = ft_read(fd, stock);
	if (!stock || !stock[0])
	{
		if (stock)
			free(stock);
		stock = 0;
		return (NULL);
	}
	line = ft_getline(stock, line);
	if (!line)
		return (ft_free(&stock));
	stock = ft_getnext(stock);
	return (line);
}
