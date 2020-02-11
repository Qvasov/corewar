/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visualisation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 15:51:46 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/10 15:51:48 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_visu_cycle(t_data *data)
{
	int	i;
	int n;

	if (data->vm.cycle + data->vm.cycle_from_start > 1)
		ft_fprintf(data->visu.fd, ", [[");
	else
		ft_fprintf(data->visu.fd, "[[");
	n = -1;
	while (++n < data->vm.num_of_players)
	{
		i = -1;
		while (++i < 16)
		{
			if (data->visu.curs[n][i] > 0)
			{
				ft_fprintf(data->visu.fd, "%d, %d, %d", data->visu.curs[n][i] - 1, i + 1, n + 1);

				if (n + 1 == data->vm.num_of_players && i + 1 == 16)
					ft_fprintf(data->visu.fd, "], [");
				else
					ft_fprintf(data->visu.fd, ", ");
			}
		}
	}

	i = -1;
	while(++i < MEM_SIZE)
	{
		if (data->visu.arena[i] > 0)
		{
			if (i + 1 == MEM_SIZE)
				ft_fprintf(data->visu.fd, "%d, %d], [%d]]", i, data->visu.arena[i], data->vm.cycles_to_die);
			else
				ft_fprintf(data->visu.fd, "%d, %d, ", i, data->visu.arena[i]);
		}
	}
}

static void	change_arena(t_data *data, int32_t addr, t_int arg)
{
	int64_t	buf;
	int		i;

	i = -1;
	while (++i < 4)
	{
		buf = (data->visu.arena[addr % MEM_SIZE] / 1000) * 1000;
		data->visu.arena[(addr + i) % MEM_SIZE] = arg.byte[3 - i];
		data->visu.arena[addr % MEM_SIZE] += buf;
	}
}

void 		ft_visu_st(t_types_code args_code, t_data *data, t_cur *cursor)
{
	t_int	arg[op_tab[cursor->op_code].args_count];
	int32_t	addr;
	int8_t	args_size;


	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg2];
	cursor->byte_to_next_op = args_size;
	if (args_code.arg2 == REG_CODE)
		cursor->reg[arg[1].num - 1] = cursor->reg[arg[0].num - 1];
	else if (args_code.arg2 == IND_CODE)
	{
		arg[0].num = cursor->reg[arg[0].num - 1]; //конвертация номера регистра в значение, которое находтся в регистре
		arg[1].num = arg[1].num % IDX_MOD;
		addr = cursor->pc + arg[1].num;
		if (addr < 0)
			addr = MEM_SIZE + (addr % MEM_SIZE);
		change_arena(data, addr, arg[0]);
	}
}

void 		ft_visu_sti(t_types_code args_code, t_data *data, t_cur *cursor)
{
	t_int	arg[3];
	int32_t	addr;
	int8_t	args_size;

	args_size = 2;
	arg[0].num = get_arg(args_code.arg1, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg1];
	arg[1].num = get_arg(args_code.arg2, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg2];
	arg[2].num = get_arg(args_code.arg3, args_size, data->vm.arena, cursor);
	args_size += data->vm.size[args_code.arg3];
	cursor->byte_to_next_op = args_size;
	if (args_code.arg2 == REG_CODE)
		arg[1].num = cursor->reg[arg[1].num - 1];
	else if (args_code.arg2 == IND_CODE)
		arg[1].num = get_ind_value(arg[1], cursor, data->vm.arena);
	if (args_code.arg3 == REG_CODE)
		arg[2].num = cursor->reg[arg[2].num - 1];
	arg[0].num = cursor->reg[arg[0].num - 1];
	addr = cursor->pc + ((arg[1].num + arg[2].num) % IDX_MOD);
	if (addr < 0)
		addr = MEM_SIZE + (addr % MEM_SIZE);
	change_arena(data, addr, arg[0]);
}

void		ft_visu_cur(t_data *data, t_cur *cursor)
{
	int		num_player;

	num_player = cursor->reg[0] * -1;
	if (num_player > 0 && num_player <= data->vm.num_of_players)
		++data->visu.curs[num_player - 1][cursor->op_code - 1];
	data->visu.arena[cursor->pc] += 1000;
}

static void	memory(t_data *data)
{
	t_cur	*cur;
	int		i;

	i = -1;
	cur = data->vm.cursor;
	ft_fprintf(data->visu.fd, "const memory_init = [");
	while (cur && cur->next)
		cur = cur->next;
	while (++i < MEM_SIZE)
	{
		if (cur && i == cur->pc)
		{
			ft_fprintf(data->visu.fd, "%d", data->vm.arena[i] + 1000);
			cur = cur->prev;
		}
		else
			ft_fprintf(data->visu.fd, "%d", data->vm.arena[i]);
		if (i + 1 == MEM_SIZE)
			ft_fprintf(data->visu.fd, "];\n");
		else
			ft_fprintf(data->visu.fd, ", ");
	}
}

static void	champions(t_data *data)
{
	int	i;

	ft_fprintf(data->visu.fd, "const champion = [");
	i = -1;
	while (++i < data->vm.num_of_players)
	{
		ft_fprintf(data->visu.fd, "[\"%s\", \"%s\", %d]",
		data->player[i].name, data->player[i].comment, data->player[i].id);
		if (i + 1 == data->vm.num_of_players)
			ft_fprintf(data->visu.fd, "];\n");
		else
			ft_fprintf(data->visu.fd, ", ");
	}
}

void		ft_init_visu(t_data *data)
{
	int	i;

	i = -1;
	if ((data->visu.fd = open("visual.js", O_WRONLY | O_CREAT | O_TRUNC,
			S_IRWXU | S_IRWXG | S_IRWXO)) < 0)
		ft_perror();
	if (!(data->visu.curs = (int **)malloc(sizeof(int *) * data->vm.num_of_players)))
		ft_perror();
	while (++i < data->vm.num_of_players)
	{
		if (!(data->visu.curs[i] = (int *)malloc(sizeof(int) * 16)))
			ft_perror();
		ft_bzero(data->visu.curs[i], sizeof(int) * 16);
	}
	ft_bzero(data->visu.arena, MEM_SIZE);
	champions(data);
	memory(data);
	ft_fprintf(data->visu.fd, "const cycle = [");
}
