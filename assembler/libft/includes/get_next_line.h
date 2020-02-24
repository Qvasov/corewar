/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:15:06 by laleta            #+#    #+#             */
/*   Updated: 2019/09/04 21:15:08 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

# define BUFF_SIZE 40

typedef struct		s_lists
{
	void			*data;
	struct s_lists	*next;
}					t_lists;

typedef struct		s_clist
{
	t_lists			*list;
	t_lists			*parent_node;
	size_t			list_size;
}					t_clist;

typedef struct		s_fileb
{
	int				fd;
	char			*buffer;
}					t_fileb;

int					ft_get_next_line(const int fd, char **line);
char				*ft_strmerge(char *s1, const char *s2, size_t len);
t_lists				*ft_clist_new(t_clist *clist, void *data);
t_lists				*ft_clist_insert(t_clist *clist, t_lists *current,
																	void *data);
void				ft_clist_del_node(t_clist *clist, t_lists **node,
														void (*del)(void**));
t_lists				*ft_clist_find_prev(t_lists *wall);

#endif
