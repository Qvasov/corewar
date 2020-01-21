/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cw_vm_read.c                                    :+:      :+:    :+:   */
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

	i = 4;
	while (i--)
		exec.byte[i] = str[3 - i];
	return (exec.num);
}

static void	valid_magic(char *str)
{
	t_int	magic;
	int		i;

	i = 4;
	while (i--)
		magic.byte[i] = str[3 - i];
	(magic.num != COREWAR_EXEC_MAGIC) ? ft_error(1) : 0; //ошибка мэджика
}

void ft_cw_vm_read(t_players *players)
{
	int 	i;
	char	*str;

	i = -1;
	while (++i < players->number_of_players)
	{
		str = ft_create_buf(players->path[i]);
		valid_magic(str); //проверка magic
		players->player[i].id = i + 1;
		ft_memcpy(players->player[i].name, &str[4], PROG_NAME_LENGTH); //считывание имени игрока
		players->player[i].exec_size = exec_size(&str[PROG_NAME_LENGTH + 8]); //считывание размера исполняемого кода
		(players->player[i].exec_size > CHAMP_MAX_SIZE) ? ft_error(1) : 0; //проверка на превышение размера чемпиона
		ft_memcpy(players->player[i].comment, &str[PROG_NAME_LENGTH + 12], COMMENT_LENGTH); //считывание коммента игрока
		ft_memcpy(players->player[i].exec_code, &str[PROG_NAME_LENGTH + COMMENT_LENGTH + 16], players->player[i].exec_size); // сичтывание exec кода
	}
}
