/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_valid_players.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:29:04 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/25 14:29:05 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	valid_exec_size(char *str, int exec_size)
{
	t_int	exec;
	int		i;

	i = INT_SIZE;
	while (i--)
		exec.byte[i] = str[INT_SIZE - 1 - i];
	if (exec.num != exec_size)
		ft_error("invalid execute code size");
}

static void	valid_str(char *str, int maxlen)
{
	int		rest_nulls;
	int		len;
	t_int	null;
	int		i;

	i = -1;
	while (++i < INT_SIZE)
		null.byte[INT_SIZE - 1 - i] = str[maxlen + i];
	(null.num != 0) ? ft_error("no name nullbytes found") : 1;
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

static void	valid_magic(char *str)
{
	t_int	magic;
	int8_t	i;
	int8_t	size;

	size = INT_SIZE;
	i = size;
	while (i--)
		magic.byte[i] = str[size - (i + 1)];
	(magic.num != COREWAR_EXEC_MAGIC) ? ft_error("cannot execute file") : 0;
}

static void	read_data(t_champ *player, char *str, int max)
{
	int		fd;
	int		ret;
	int		ret_total;
	char	*ptr;

	ret_total = 0;
	(fd = open(player->path, O_RDONLY)) < 0 ? ft_perror(NULL) : 1;
	ptr = str;
	while (ret_total <= max && (ret = read(fd, ptr, max + 1 - ret_total)) > 0)
	{
		ptr += ret;
		ret_total += ret;
	}
	(ret < 0) ? ft_perror(NULL) : 1;
	player->exec_size = ret_total - (max - CHAMP_MAX_SIZE);
	if (ret != 0 || player->exec_size > CHAMP_MAX_SIZE || player->exec_size < 0)
		ft_error("invalid size of file");
	(close(fd)) < 0 ? ft_perror(NULL) : 1;
}

void		ft_read_valid_players(t_vm *vm, t_champ *player, int max_size)
{
	int		i;
	char	*str;
	int16_t	delta;

	delta = 0;
	(!(str = (char *)ft_memalloc(max_size + 1))) ? ft_perror(NULL) : 1;
	i = -1;
	while (++i < vm->num_of_players)
	{
		read_data(&player[i], str, max_size);
		valid_magic(str);
		ft_memcpy(player[i].name, &str[INT_SIZE], PROG_NAME_LENGTH + 4);
		valid_str(player[i].name, PROG_NAME_LENGTH);
		valid_exec_size(&str[PROG_NAME_LENGTH + 4 * 2], player[i].exec_size);
		ft_memcpy(player[i].comment, &str[PROG_NAME_LENGTH + 4 * 3],
				COMMENT_LENGTH + 4);
		valid_str(player[i].comment, COMMENT_LENGTH);
		ft_memcpy(&vm->arena[delta],
				&str[PROG_NAME_LENGTH + COMMENT_LENGTH + 4 * 4],
				player[i].exec_size);
		delta += ((MEM_SIZE) / vm->num_of_players);
		player[i].id = i + 1;
		ft_bzero(str, max_size);
	}
	free(str);
}
