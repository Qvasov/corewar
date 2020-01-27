#include "vm.h"

static int	valid_number_reg(t_types_code args_code, t_cur *cursor, t_vm *vm)
{
	int16_t	reg_pos;

	if (args_code.arg1 == 1)
	{
		reg_pos = (cursor->pc + 2) % MEM_SIZE;
		if (!(vm->arena[reg_pos] >= 1 && vm->arena[reg_pos] <= 16))
			return (1);
	}
	if (args_code.arg2 == 1)
	{
		reg_pos = (cursor->pc + 3) % MEM_SIZE;
		if (!(vm->arena[reg_pos] >= 1 && vm->arena[reg_pos] <= 16))
			return (1);
	}
	if (args_code.arg3 == 1)
	{
		reg_pos = (cursor->pc + 4) % MEM_SIZE;
		if (!(vm->arena[reg_pos] >= 1 && vm->arena[reg_pos] <= 16))
			return (1);
	}
	return (0);
}

int			ft_valid_op_code_and_reg(t_vm *vm, t_cur *cursor, int8_t (**valid) (int8_t))
{
	t_types_code	args_code;

	if (op_tab[cursor->op_code].args_type_code)
	{
		args_code.num = vm->arena[(cursor->pc + 1) % MEM_SIZE];
		if (valid[args_code.arg1](op_tab[cursor->op_code].args.code.types1) ||
			valid[args_code.arg2](op_tab[cursor->op_code].args.code.types2) ||
			valid[args_code.arg3](op_tab[cursor->op_code].args.code.types3) ||
			valid[args_code.arg4](op_tab[cursor->op_code].args.code.types4) ||
			valid_number_reg(args_code, cursor, vm))
			return (1); //если не корректен код типов аргументов или номер регистра
	}
	return (0);
}
