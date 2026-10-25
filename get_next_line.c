/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 14:31:13 by aaydogdu          #+#    #+#             */
/*   Updated: 2026/10/26 01:22:09 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_stash(t_list **stash, int fd)
{
	char	*buf; //her turdaki okuma bufferı
	int		bytes; //readin dönüş değeri

	while (!has_new_line(*stash))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (0);
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes <= 0)
		{
			free(buf);
			return (bytes == 0);
		}
		buf[bytes] = '\0';
		if (lst_add_back(stash, buf) == 0)
		{
			free(buf);
			return (0); //1 dönerse sahiplik düğüme geçti, başarıyla oluştu. 0 dönerse kontrol bizde, düğüm oluşamadı
		}
	}
	return (1);
}
//stashin başından \n görene kadar mallocla yer ayırıp tek bir stringe kopyalıyo arkadaş
static char	*extract_line(t_list *stash)
{
	char	*line;
	int		i;
	int		j;
	int		len;

	len = line_len(stash);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stash && i < len)
	{
		j = 0;
		while (stash->content[j] && i < len)
		{
			line[i] = stash->content[j];
			i++;
			j++;
		}
		stash = stash->next;
	}
	line[i] = '\0';
	return (line);
}

static t_list	*clean_stash(t_list *stash) {}

char	*get_next_line(int fd)
{
	static t_list	*stash;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_stash(&stash, fd) == 0)
	{
		free_list(stash);
		stash = NULL;
		return (NULL);
	}
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
	{
		free_list(stash);
		stash = NULL;
		return NULL;
	}
	stash = clean_stash(stash);
	return (line);
}
