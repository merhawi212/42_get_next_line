/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:22:38 by mkiflema          #+#    #+#             */
/*   Updated: 2023/01/12 18:22:39 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		len = 0;
	while (*s++)
		++len;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c > 255)
		c = c % 256;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == c)
		return ((char *)(s + i));
	return (0);
}

char	*ft_strjoin(char *saved, char *buff)
{
	char	*joined_str;
	int		i;
	int		j;

	if (!saved)
	{
		saved = (char *)malloc(1 * sizeof(char));
		saved[0] = '\0';
	}
	j = ft_strlen(saved) + ft_strlen(buff);
	joined_str = (char *)malloc((j + 1) * sizeof(char));
	if (!joined_str)
		return (0);
	i = -1;
	j = 0;
	if (saved)
		while (saved[++i] != '\0')
			joined_str[i] = saved[i];
	while (buff[j])
		joined_str[i++] = buff[j++];
	joined_str[i] = '\0';
	free(saved);
	return (joined_str);
}
