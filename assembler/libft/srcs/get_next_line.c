/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:16:37 by laleta            #+#    #+#             */
/*   Updated: 2019/09/04 21:16:39 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	t_lists	*ft_new_file(t_clist *clist, t_lists *current, const int fd)
{
	t_fileb	*file_set;

	if (!(file_set = (t_fileb *)malloc(sizeof(*file_set))))
		return (NULL);
	file_set->buffer = NULL;
	file_set->fd = fd;
	if (!current)
		return (ft_clist_new(clist, file_set));
	return (ft_clist_insert(clist, current, file_set));
}

static t_lists	*ft_search_file(t_clist *clist, const int fd)
{
	t_lists	*list;
	size_t	size;
	t_fileb	*file_set;

	list = clist->list;
	size = clist->list_size;
	if (size)
		while (1)
		{
			file_set = list->data;
			if (file_set->fd == fd)
				return (list);
			if (!--size)
				break ;
			list = list->next;
		}
	return (ft_new_file(clist, list, fd));
}

static int		ft_file_parse(const int fd, t_fileb **file_set,
															char **next_line)
{
	char	*readed;
	size_t	len;
	int		ret;

	if (!(readed = ft_strnew(BUFF_SIZE)))
		return (-1);
	len = BUFF_SIZE;
	ret = 1;
	if ((*file_set)->buffer)
		len += ft_strlen((*file_set)->buffer);
	while (!(*next_line = ft_strchr((*file_set)->buffer, '\n')))
	{
		if (((ret = read(fd, readed, BUFF_SIZE)) == -1))
			break ;
		readed[ret] = '\0';
		if (!((*file_set)->buffer =
					ft_strmerge((*file_set)->buffer, readed, len)))
			ret = -1;
		if (ret <= 0)
			break ;
		len += BUFF_SIZE;
	}
	free(readed);
	return (ret);
}

static int		ft_last_line(char **line, char **buffer, t_clist *clist,
																t_lists **node)
{
	if (*buffer)
		if (**buffer)
		{
			if (!(*line = ft_strdup(*buffer)))
				return (-1);
			ft_strdel(buffer);
			ft_clist_del_node(clist, node, ft_memdel);
			return (1);
		}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_clist	clist;
	t_lists			*node;
	t_fileb			*file_set;
	char			*tmp[2];
	int				ret;

	if (!line || !(node = ft_search_file(&clist, fd)))
		return (-1);
	file_set = node->data;
	if (((ret = ft_file_parse(fd, &file_set, &tmp[1])) <= 0))
	{
		if (ret == -1)
			return (-1);
		return (ft_last_line(line, &file_set->buffer, &clist, &node));
	}
	if (!(*line = ft_strsub(file_set->buffer, 0, (tmp[1] - file_set->buffer))))
		return (-1);
	tmp[0] = file_set->buffer;
	file_set->buffer = ft_strdup(tmp[1] + 1);
	free(tmp[0]);
	clist.list = node;
	return (1);
}
