/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 14:31:13 by aaydogdu          #+#    #+#             */
/*   Updated: 2026/10/21 18:09:31 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_stash(t_list **stash, int fd)
{

}

static char	*extract_line(t_list *stash) {}

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
