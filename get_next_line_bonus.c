/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:58:04 by aaydogdu          #+#    #+#             */
/*   Updated: 2024/12/15 11:58:04 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*joinfunc(char *str, char *buffer, int fd)
{
	int	count;

	count = 1;
	while (!ft_strchr(str, '\n') && count != 0)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
		{
			free(str);
			free(buffer);
			return (NULL);
		}
		buffer[count] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*getbefore(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*getafter(char *str)
{
	char	*afternl;
	int		i;
	int		j;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	afternl = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!afternl)
		return (NULL);
	j = 0;
	i++;
	while (str[i])
		afternl[j++] = str[i++];
	afternl[j] = '\0';
	free(str);
	return (afternl);
}

char	*get_next_line(int fd)
{
	char		*result;
	char		*buffer;
	static char	*str[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	str[fd] = joinfunc(str[fd], buffer, fd);
	if (!str[fd])
		return (NULL);
	result = getbefore(str[fd]);
	str[fd] = getafter(str[fd]);
	return (result);
}
