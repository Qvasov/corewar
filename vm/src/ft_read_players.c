/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 19:48:23 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/21 19:48:28 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int exec_size(char *str)
{
	t_int	exec;
	int		i;

	i = INT_SIZE;
	while (i--)
		exec.byte[i] = str[3 - i];
	return (exec.num);
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
	(magic.num != COREWAR_EXEC_MAGIC) ? ft_error("cannot execute file") : 0; //ошибка мэджика
}

static void	read_data(char *path, char *str, int max)
{
	int		fd;
	int 	ret;
	int 	ret_total;
	char	*data;
	int		weight;

	ret_total = 0;
	(fd = open(path, O_RDONLY)) < 0 ? ft_perror() : 1;
	data = str;
	while (max >= ret_total && (ret = read(fd, data, max + 1 - ret_total)) > 0)
	{
		data += ret;
		ret_total += ret;
	}
	(ret < 0) ? ft_perror() : 1;
	weight = ret_total - (max - CHAMP_MAX_SIZE);
	if (ret != 0 || weight > CHAMP_MAX_SIZE || weight < 0)//check
		ft_error("invalid size of file");
	(close(fd)) < 0 ? ft_perror() : 1;
}

void 		ft_read_players(t_vm *vm, t_champ *player)
{
	int 	i;
	char	*str;
	int		max_size;
	int16_t	delta;

	delta = 0;
	max_size = PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE + 4 * 4;
	(!(str = (char *)ft_memalloc(max_size + 1))) ? ft_perror() : 1;
	i = -1;
	while (++i < vm->num_of_players)
	{
		read_data(player[i].path, str, max_size);
		valid_magic(str); //проверка magic
		player[i].id = i + 1;
		ft_memcpy(player[i].name, &str[INT_SIZE], PROG_NAME_LENGTH); //считывание имени игрока
		player[i].exec_size = exec_size(&str[PROG_NAME_LENGTH + INT_SIZE + 4]); //считывание размера исполняемого кода
		(player[i].exec_size > CHAMP_MAX_SIZE) ? ft_error(1) : 0; //проверка на превышение размера чемпиона
		ft_memcpy(player[i].comment, &str[PROG_NAME_LENGTH + INT_SIZE + 4 + INT_SIZE], COMMENT_LENGTH); //считывание коммента игрока
		//проверка на по весу
		ft_memcpy(&vm->arena[delta], &str[PROG_NAME_LENGTH + COMMENT_LENGTH + INT_SIZE + 4 + INT_SIZE + 4], player[i].exec_size); // сичтывание exec кода
		delta += ((MEM_SIZE) / vm->num_of_players);
		ft_bzero(str, max_size);
	}
}
