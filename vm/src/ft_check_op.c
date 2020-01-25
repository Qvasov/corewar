#include "vm.h"



static int	valid_number_reg(t_types_code args_code, t_cursor *cursor, t_vm *vm)
{
	int16_t	reg_pos;

	if (args_code.arg4 == 1)
	{
		reg_pos = (cursor->position + 2) % MEM_SIZE;
		if (!(vm->arena[reg_pos] >= 1 && vm->arena[reg_pos] <= 16))
			return (1);
	}
	if (args_code.arg3 == 1)
	{
		reg_pos = (cursor->position + 3) % MEM_SIZE;
		if (!(vm->arena[reg_pos] >= 1 && vm->arena[reg_pos] <= 16))
			return (1);
	}
	if (args_code.arg2 == 1)
	{
		reg_pos = (cursor->position + 4) % MEM_SIZE;
		if (!(vm->arena[reg_pos] >= 1 && vm->arena[reg_pos] <= 16))
			return (1);
	}
	return (0);
}

int			ft_check_op(t_vm *vm, t_cursor *cursor, int8_t (**valid) (int8_t))
{
	t_types_code	args_code;

//	cursor->byte_to_next_op = 2;
	if (op_tab[cursor->op_code].args_type_code)
	{
		args_code.num = vm->arena[(cursor->position + 1) % MEM_SIZE];
		if (valid[args_code.arg4](op_tab[cursor->op_code].args.code.types1) ||
			valid[args_code.arg3](op_tab[cursor->op_code].args.code.types2) ||
			valid[args_code.arg2](op_tab[cursor->op_code].args.code.types3) ||
			valid[args_code.arg1](op_tab[cursor->op_code].args.code.types4))
			return (1);
//		cursor->byte_to_next_op = size_op(cursor->op_code, args_code, vm->size);
		if (valid_number_reg(args_code, cursor, vm))
			return (1); //если не корректен код типов аргументов или номер регистра
	}
	return (0);
}
