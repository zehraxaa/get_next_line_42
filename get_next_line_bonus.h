/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaydogdu <aaydogdu@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 00:20:10 by aaydogdu          #+#    #+#             */
/*   Updated: 2026/10/30 00:34:18 by aaydogdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#ifndef MAX_FD
# define MAX_FD 1048576 // ulimit -n yaptım terminalde
#endif

#include <unistd.h>
#include <stdlib.h>

typedef struct s_list
{
	char			*content; //node, veriyi tutar (burdaki veri de okunan satır)
	struct s_list	*next; //diğerinin adresini tutar
}	t_list;

char	*get_next_line(int fd);
t_list	*lst_last(t_list *list);
int		lst_add_back(t_list **list, char *content);
int		has_new_line(t_list *list);
int		line_len(t_list *list);
void	free_list(t_list *list);

#endif