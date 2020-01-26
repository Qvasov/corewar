#include "vm.h"

static int32_t	get_value(uint8_t arg_code, int8_t arg_pos, uint8_t *arena, t_cursor *cursor)
{
	t_int	ret;
	int8_t	i;
	int8_t	j;

	ret.num = 0;
	if (arg_code == REG_CODE)
		ret.num = arena[(cursor->position + arg_pos) % MEM_SIZE];
	else
	{
		i = -1;
		j = (arg_code == DIR_CODE && !op_tab[cursor->op_code].dir_size) ? 3 : 1;
		while (++i <= j)
			ret.byte[j - i] = arena[(cursor->position + arg_pos + i) % MEM_SIZE];
	}
	/*else if (arg_code == DIR_CODE)
	{
		if (op_tab[cursor->op_code].dir_size)
		{
			ret.byte[1] = arena[(cursor->position + arg_pos) % MEM_SIZE];
			ret.byte[0] = arena[(cursor->position + arg_pos + 1) % MEM_SIZE];
		}
		else
		{
			ret.byte[3] = arena[(cursor->position + arg_pos) % MEM_SIZE];
			ret.byte[2] = arena[(cursor->position + arg_pos + 1) % MEM_SIZE];
			ret.byte[1] = arena[(cursor->position + arg_pos + 2) % MEM_SIZE];
			ret.byte[0] = arena[(cursor->position + arg_pos + 3) % MEM_SIZE];
		}
	}
	else if (arg_code == IND_CODE)
	{
		ret.byte[1] = arena[(cursor->position + arg_pos) % MEM_SIZE];
		ret.byte[0] = arena[(cursor->position + arg_pos + 1) % MEM_SIZE];
	}*/
	return (ret.num);
}

static void	live(t_types_code args_code, t_vm *vm, t_cursor *cursor)
{
	t_int	arg;
	int8_t	args_size;

	args_size = 2;
	arg.num = get_value(args_code.arg1, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg1];
	cursor->byte_to_next_op = args_size;
//	if (arg.num ==)
}

static void	ld(t_types_code args_code, t_vm *vm, t_cursor *cursor)
{
	t_int	arg[2];
	int32_t	addr;
	int8_t	args_size;

	args_size = 2;
	arg[0].num = get_value(args_code.arg1, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg1];
	arg[1].num = get_value(args_code.arg2, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg2];
	cursor->byte_to_next_op = args_size;
	if (args_code.arg1 == IND_CODE) //получение числа по адресу
	{
		arg[0].num = arg[0].num % IDX_MOD;
		addr = ((cursor->position + arg[0].num) % IDX_MOD);
		arg[0].byte[3]= vm->arena[addr % MEM_SIZE];
		arg[0].byte[2]= vm->arena[(addr + 1) % MEM_SIZE];
		arg[0].byte[1]= vm->arena[(addr + 2) % MEM_SIZE];
		arg[0].byte[0]= vm->arena[(addr + 3) % MEM_SIZE];
	}
	cursor->reg[arg[1].num - 1] = arg[0].num;
	cursor->carry = (cursor->reg[arg[1].num - 1] == 0) ? 1 : 0;
}

static void	st(t_types_code args_code, t_vm *vm, t_cursor *cursor)
{
	t_int	arg[2];
	int32_t	addr;
	int8_t	args_size;

	args_size = 2;
	arg[0].num = get_value(args_code.arg1, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg1];
	arg[1].num = get_value(args_code.arg2, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg2];
	cursor->byte_to_next_op = args_size;
	if (args_code.arg2 == REG_CODE)
		cursor->reg[arg[1].num - 1] = cursor->reg[arg[0].num - 1];
	else if (args_code.arg2 == IND_CODE)
	{
		arg[0].num = cursor->reg[arg[0].num - 1]; //конвертация номера регистра в значение, которое находтся в регистре
		arg[1].num = arg[1].num % IDX_MOD;
		addr = ((cursor->position + arg[1].num) % IDX_MOD);
		vm->arena[addr % MEM_SIZE] = arg[0].byte[3];
		vm->arena[(addr + 1) % MEM_SIZE] = arg[0].byte[2];
		vm->arena[(addr + 2) % MEM_SIZE] = arg[0].byte[1];
		vm->arena[(addr + 3) % MEM_SIZE] = arg[0].byte[0];
	}
}

static void	add(t_types_code args_code, t_vm *vm, t_cursor *cursor)
{
	t_int	arg[3];
	int8_t	args_size;

	args_size = 2;
	arg[0].num = get_value(args_code.arg1, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg1];
	arg[1].num = get_value(args_code.arg2, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg2];
	arg[2].num = get_value(args_code.arg3, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg3];
	cursor->byte_to_next_op = args_size;
	cursor->reg[arg[2].num] = cursor->reg[arg[0].num] + cursor->reg[arg[1].num];
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}

static void	sub(t_types_code args_code, t_vm *vm, t_cursor *cursor)
{
	t_int	arg[3];
	int8_t	args_size;

	args_size = 2;
	arg[0].num = get_value(args_code.arg1, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg1];
	arg[1].num = get_value(args_code.arg2, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg2];
	arg[2].num = get_value(args_code.arg3, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg3];
	cursor->byte_to_next_op = args_size;
	cursor->reg[arg[2].num] = cursor->reg[arg[0].num] - cursor->reg[arg[1].num];
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}

static void	and(t_types_code args_code, t_vm *vm, t_cursor *cursor)
{
	t_int	arg[3];
	int8_t	args_size;

	args_size = 2;
	arg[0].num = get_value(args_code.arg1, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg1];
	arg[1].num = get_value(args_code.arg2, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg2];
	arg[2].num = get_value(args_code.arg3, args_size, vm->arena, cursor);
	args_size += vm->size[args_code.arg3];
	cursor->byte_to_next_op = args_size;
	if (args_code.arg1 == ) //tut ostanovochka

	cursor->reg[arg[2].num] = ;
	cursor->carry = (cursor->reg[arg[2].num - 1] == 0) ? 1 : 0;
}

void	ft_init_op(void (**op) (t_types_code, t_vm *, t_cursor *))
{
	op[0];
	op[1] = live;
	op[2] = ld;
	op[3] = st;
	op[4] = add;
	op[5] = sub;
	op[6] = and;
}
