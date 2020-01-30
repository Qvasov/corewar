#include "vm.h"

int		get_value(t_int arg, t_cur *cursor, uint8_t *arena)
{
	int32_t	addr;

	addr = cursor->pc + arg.num;
	if (addr < 0)
		addr = MEM_SIZE + (addr % MEM_SIZE);
	arg.byte[3]= arena[addr % MEM_SIZE];
	arg.byte[2]= arena[(addr + 1) % MEM_SIZE];
	arg.byte[1]= arena[(addr + 2) % MEM_SIZE];
	arg.byte[0]= arena[(addr + 3) % MEM_SIZE];
	return (arg.num);
}

int		get_arg(uint8_t arg_code, int8_t arg_pos, uint8_t *arena, t_cur *cursor)
{
	t_int	ret;
	int8_t	i;
	int8_t	j;

	ret.num = 0;
	if (arg_code == REG_CODE)
		ret.num = arena[(cursor->pc + arg_pos) % MEM_SIZE];
	else
	{
		i = -1;
		j = (arg_code == DIR_CODE && !op_tab[cursor->op_code].dir_size) ? 3 : 1;
		while (++i <= j)
			ret.byte[j - i] = arena[(cursor->pc + arg_pos + i) % MEM_SIZE];
		if (j == 1)
			ret.num = (int16_t)ret.num;
	}
	return (ret.num);
}

void	ft_init_op(void (**op) (t_types_code, t_vm *, t_cur *))
{
	op[0] = NULL;
	op[1] = live;
	op[2] = ld;
	op[3] = st;
	op[4] = add;
	op[5] = sub;
	op[6] = and;
	op[7] = or;
	op[8] = xor;
	op[9] = zjmp;
	op[10] = ldi;
	op[11] = sti;
	op[12] = fork_cw;
	op[13] = lld;
	op[14] = lldi;
	op[15] = lfork_cw;
	op[16] = aff;
}
