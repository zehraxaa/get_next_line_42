/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 14:31:47 by aaydogdu          #+#    #+#             */
/*   Updated: 2026/10/19 14:31:48 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

#include <unistd.h>
#include <stdlib.h>

typedef struct s_list
{
	char			*content; //node, veriyi tutar (burdaki veri de okunan satır)
	struct s_list	*next; //diğerinin adresini tutar
}   t_list;

char	*get_next_line(int fd);
t_list	*lst_last(t_list *list);
int		lst_add_back(t_list **list, char *content);

#endif