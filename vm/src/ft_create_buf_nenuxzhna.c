/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 19:47:55 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/21 19:47:56 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char	*bufdup(char *buf, size_t size)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)malloc(size);
	while (i < size)
	{
		str[i] = buf[i];
		i++;
	}
	return (str);
}

static char	*bufjoin(char *buf1, char *buf2, size_t size1, size_t size2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	str = (char *)malloc(size1 + size2);
	while (i < size1)
	{
		str[i] = buf1[i];
		i++;
	}
	j = 0;
	while (j < size2)
	{
		str[i + j] = buf2[j];
		j++;
	}
	return (str);
}

char		*ft_create_buf(char *path)
{
	int		fd;
	int		ret;
	int		size;
	char	buf[BUFF_SIZE];
	char 	*str;

	((fd = open(path, O_RDONLY)) < 0) ? ft_perror(NULL) : 0;
	str = NULL;
	size = 0;
	while ((ret = read(fd, &buf, BUFF_SIZE)) > 0)
	{
		str = (char *)realloc(str, size + ret);

		size += ret;


//		str = (tmp) ? bufjoin(tmp, buf, BUFF_SIZE, ret) : bufdup(buf, ret);
//		(tmp) ? free(tmp) : 0; //realloc
	}
	(ret < 0) ? ft_perror(NULL) : 0;
	(close(fd) < 0) ? ft_perror(NULL) : 0;
	return (str);
}
