/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 00:27:12 by aaydogdu          #+#    #+#             */
/*   Updated: 2026/10/30 00:29:46 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
//parametre, son düğümün contenti
static char	*copy_rest(char *content)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	while (content[i] != '\0' && content[i] != '\n')
		i++;
	if (content[i] == '\0' || !content[++i])
		return NULL;
	j = 0;
	while (content[i + j] != '\0')
		j++;
	rest = malloc(j + 1);
	if (!rest)
		return NULL;
	j = 0;
	while (content[i] != '\0')
		rest[j++] = content[i++];
	rest[j] = '\0';
	return (rest);
}

static t_list	*clean_stash(t_list *stash)
{
	t_list	*new;
	t_list	*last;
	char	*rest;

	new = NULL;
	rest = NULL;
	last = lst_last(stash);
	if (last)
		rest = copy_rest(last->content);
	free_list(stash);
	if (!rest)
		return NULL;
	if (!lst_add_back(&new, rest))
	{	
		free(rest);
		return NULL;
	}
	return (new);
}

char	*get_next_line(int fd)
{
	static t_list	*stash[MAX_FD];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	if (read_stash(&stash[fd], fd) == 0)
	{
		free_list(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	if (!line)
	{
		free_list(stash[fd]);
		stash[fd] = NULL;
		return NULL;
	}
	stash[fd] = clean_stash(stash);
	return (line);
}
