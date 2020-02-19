#include "vm.h"

static int	valid_number_reg(t_types_code args_code, t_cur *cursor, t_vm *vm, const int8_t *size)
{
	int16_t	reg_pos;

	if (args_code.arg1 == REG_CODE)
	{
		reg_pos = (cursor->pc + 2) % MEM_SIZE;
		if (!(vm->arena[reg_pos] >= 1 && vm->arena[reg_pos] <= 16))
			return (1);
	}
	if (args_code.arg2 == REG_CODE)
	{
		reg_pos = (cursor->pc + 2 + size[args_code.arg1]) % MEM_SIZE;
		if (!(vm->arena[reg_pos] >= 1 && vm->arena[reg_pos] <= 16))
			return (1);
	}
	if (args_code.arg3 == REG_CODE)
	{
		reg_pos = (cursor->pc + 2 + size[args_code.arg1] +
				size[args_code.arg2]) % MEM_SIZE;
		if (!(vm->arena[reg_pos] >= 1 && vm->arena[reg_pos] <= 16))
			return (1);
	}
	return (0);
}

int			ft_valid_op_code_and_reg(t_data *data, t_cur *cursor)
{
	t_types_code	args_code;

	if (op_tab[cursor->op_code].args_type_code)
	{
		args_code.num = data->vm.arena[(cursor->pc + 1) % MEM_SIZE];
		if (data->valid[args_code.arg1](0, cursor->op_code) ||
			data->valid[args_code.arg2](1, cursor->op_code) ||
			data->valid[args_code.arg3](2, cursor->op_code) ||
			data->valid[args_code.arg4](3, cursor->op_code) ||
			valid_number_reg(args_code, cursor, &data->vm, data->size)) //отдельно рега без кода типов нету
			return (1); //если не корректен код типов аргументов или номер регистра
	}
	return (0);
}
