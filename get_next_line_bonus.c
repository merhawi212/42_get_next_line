/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:23:28 by mkiflema          #+#    #+#             */
/*   Updated: 2023/01/25 21:03:59 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_line(char *saved)
{
	char	*line;
	int		i;

	i = 0;
	if (!saved[i])
		return (NULL);
	while (saved[i] != '\n' && saved[i])
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (saved[i] != '\n' && saved[i])
	{
		line[i] = saved[i];
		i++;
	}
	if (saved[i] == '\n')
	{
		line[i] = saved[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next(char *saved)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	while (saved[i] != '\n' && saved[i])
		i++;
	if (!saved[i])
	{
		free(saved);
		return (NULL);
	}
	next = malloc(sizeof(char) * (ft_strlen(saved) - i + 1));
	if (!next)
		return (NULL);
	i++;
	j = 0;
	while (saved[i])
		next[j++] = saved[i++];
	next[j] = '\0';
	free(saved);
	return (next);
}

char	*read_and_add(int fd, char *saved)
{
	char	*buff;
	int		readed_bytes;

	buff = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	readed_bytes = 1;
	while (!(ft_strchr(saved, '\n')) && readed_bytes > 0)
	{
		readed_bytes = read(fd, buff, BUFFER_SIZE);
		if (readed_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[readed_bytes] = '\0';
		saved = ft_strjoin(saved, buff);
	}
	free(buff);
	return (saved);
}

char	*get_next_line(int fd)
{
	static char	*saved[256];
	char		*line;

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (NULL);
	saved[fd] = read_and_add(fd, saved[fd]);
	if (!saved[fd])
		return (NULL);
	line = get_line(saved[fd]);
	saved[fd] = get_next(saved[fd]);
	return (line);
}
