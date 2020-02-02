/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live_zjmp_fork_lfork_aff.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 19:24:34 by dbennie           #+#    #+#             */
/*   Updated: 2020/01/30 19:24:36 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	live(t_types_code args_code, t_vm *vm, t_cur *cursor)
{
	t_int	arg;
	int8_t	args_size;

	args_size = 1;
	arg.num = get_arg(args_code.arg1, args_size, vm->arena, cursor);
	args_size += vm->size[DIR_CODE];
	cursor->byte_to_next_op = args_size;
	++vm->number_of_live;
	cursor->cycle_of_last_live = vm->cycle;
	if (arg.num >= vm->min_player_id && arg.num <= vm->max_player_id)
		vm->last_player_id = (char)arg.num;
}

void	zjmp(t_types_code args_code, t_vm *vm, t_cur *cursor)
{
	t_int	arg;
	int8_t	args_size;

	args_size = 1;
	arg.num = get_arg(args_code.arg1, args_size, vm->arena, cursor);
	args_size += vm->size[DIR_CODE];
	if (cursor->carry == 1)
		cursor->byte_to_next_op = arg.num % IDX_MOD;
	else
		cursor->byte_to_next_op = args_size;
}

void	fork_cw(t_types_code args_code, t_vm *vm, t_cur *cursor)
{
	t_int	arg;
	int8_t	args_size;
	t_cur	*new_cursor;

	args_size = 1;
	arg.num = get_arg(args_code.arg1, args_size, vm->arena, cursor);
	args_size += vm->size[DIR_CODE];
	cursor->byte_to_next_op = args_size;
	new_cursor = ft_copy_cursor(vm, cursor);
	new_cursor->pc = (cursor->pc + arg.num) % IDX_MOD;;
	if (new_cursor->pc < 0)
		new_cursor->pc += MEM_SIZE;
} //тут вопросы

void	lfork_cw(t_types_code args_code, t_vm *vm, t_cur *cursor)
{
	t_int	arg;
	int8_t	args_size;
	t_cur	*new_cursor;

	args_size = 1;
	arg.num = get_arg(args_code.arg1, args_size, vm->arena, cursor);
	args_size += vm->size[DIR_CODE];
	cursor->byte_to_next_op = args_size;
	new_cursor = ft_copy_cursor(vm, cursor);
	new_cursor->pc = cursor->pc + arg.num;
	if (new_cursor->pc < 0)
		new_cursor->pc += MEM_SIZE;
} //тут вопросы как и в fork обычном

void	aff(t_types_code args_code, t_vm *vm, t_cur *cursor)
{
	t_int	arg;
	int8_t	args_size;
	char	str[2];

	args_size = 2;
	arg.num = get_arg(args_code.arg1, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg1];
	cursor->byte_to_next_op = args_size;
	arg.num = cursor->reg[arg.num - 1];
	str[0] = (char)arg.num;
	str[1] = '\n';
//	write(1, str, 2); // заклирить
}
