/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_valid_champs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 20:55:51 by ddarell           #+#    #+#             */
/*   Updated: 2020/01/29 22:37:04 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	check_valid_str(char *str, int maxlen)
{
	int	rest_nulls;
	int len;

	((ft_read_int((uint8_t *)str + maxlen)) != 0) ?//check
	ft_error("no name nullbytes found") : 1;
	len = (int)ft_strlen(str);
	rest_nulls = maxlen - len;
	str += len;
	while (rest_nulls)
	{
		if (str[rest_nulls] != 0)
			ft_error("invalid champion data");
		rest_nulls--;
	}
}

static void	valid_champ(t_champ *champ, char *str)
{
	((ft_read_int((uint8_t *)str)) != COREWAR_EXEC_MAGIC) ?//check
	ft_error("cannot execute file") : 1;
	str += 4;
	check_valid_str(str, PROG_NAME_LENGTH);
	champ->name = str;
	str += PROG_NAME_LENGTH + 4;
	((ft_read_int((uint8_t *)str)) != champ->weight) ?//check
	ft_error("invalid execute code size") : 1;
	str += 4;
	check_valid_str(str, COMMENT_LENGTH);
	champ->comment = str;
	str += COMMENT_LENGTH + 4;
	champ->exec = str;
}

static void	read_champ(t_champ *champ)
{
	int 	fd;
	int 	ret;
	int 	max;
	int 	ret_total;
	char    *data;

	max = PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE + 4 * 4;
	ret_total = 0;
	(NULL == (champ->file_data = ft_memalloc(max + 1))) ? ft_perror() : 1;
	(fd = open(champ->path, O_RDONLY)) < 0 ? ft_perror() : 1;
	data = champ->file_data;
	while (max >= ret_total && (ret = read(fd, data, max + 1 - ret_total)) > 0)
	{
		data += ret;
		ret_total += ret;
	}
	ret < 0 ? ft_perror() : 1;
	champ->weight = ret_total - (max - CHAMP_MAX_SIZE);
	if (ret != 0 || champ->weight > CHAMP_MAX_SIZE || champ->weight < 0)//check
		ft_error("invalid size of file");
	(close(fd)) < 0 ? ft_perror() : 1;
}

void		ft_read_valid_champs(t_champ *champ)
{
	int i;

	i = 0;
	while (champ[i].path)
	{
		read_champ(champ + i);
		valid_champ(champ + i, champ[i].file_data);
		champ[i].num = i + 1;
		i++;
	}
}
