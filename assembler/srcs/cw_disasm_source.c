/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_disasm_source.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:56:49 by laleta            #+#    #+#             */
/*   Updated: 2020/02/24 12:59:43 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_disasm.h"
#include "cw_asm_operation.h"

static uint8_t	write_operation(uint8_t oper, t_disasm *disassm)
{
	if (oper > 0 && oper < 17)
	{
		ft_putstr_fd(g_oper_tab[oper].name, disassm->fd_out);
		write(disassm->fd_out, " ", 1);
		return (1);
	}
	error_handle(disassm->file_name, ERR_OPERATION_INVALID, NULL, disassm);
	return (0);
}

static uint8_t	valid_arg_type(uint8_t *program, uint64_t idx)
{
	uint8_t	i;
	uint8_t	oper;
	uint8_t arg_code;

	i = 0;
	oper = program[idx];
	if (!g_oper_tab[oper].is_arg_code)
		return (1);
	arg_code = program[idx + 1];
	while (i == 0 || i < g_oper_tab[oper].arg_cnt)
	{
		if (!(g_arg_type[get_bits(i, arg_code)].code &
												g_oper_tab[oper].arg_type[i]))
			return (0);
		i++;
	}
	return (1);
}

static uint8_t	write_argument(uint8_t arg_type, uint8_t oper,
															t_disasm *disassm)
{
	int32_t	nbr;
	uint8_t	half_dir_size;
	uint8_t	size;

	nbr = 0;
	half_dir_size = g_oper_tab[oper].dir_size == 2 && arg_type == 2 ? 2 : 1;
	size = g_arg_type[arg_type].size / half_dir_size;
	write(disassm->fd_out, g_arg_type[arg_type].str,
										ft_strlen(g_arg_type[arg_type].str));
	ft_memcpy(&nbr, &disassm->program[disassm->idx], size);
	if (size == 4)
	{
		nbr = swap_byte4(nbr);
		ft_putnbr_fd(nbr, disassm->fd_out);
	}
	else if (size == 2)
	{
		nbr = swap_byte2(nbr);
		ft_putnbr_fd((int16_t)nbr, disassm->fd_out);
	}
	else
		ft_putnbr_fd((int8_t)nbr, disassm->fd_out);
	return (size);
}

static void		write_program(t_disasm *disassm)
{
	uint8_t	oper;
	uint8_t	arg_code;
	uint8_t	i;

	i = 0;
	arg_code = 128;
	if (!valid_arg_type(disassm->program, disassm->idx))
		error_handle(disassm->file_name, ERR_ARGTYPE_INVALID, NULL, disassm);
	oper = disassm->program[disassm->idx];
	disassm->idx += write_operation(oper, disassm);
	while (i == 0 || i < g_oper_tab[oper].arg_cnt)
	{
		if (i == 0 && g_oper_tab[oper].is_arg_code)
			arg_code = disassm->program[disassm->idx++];
		disassm->idx += write_argument(get_bits(i, arg_code), oper, disassm);
		if (i < g_oper_tab[oper].arg_cnt - 1)
			write(disassm->fd_out, ",", 1);
		i++;
	}
	write(disassm->fd_out, "\n", 1);
}

void			translate_to_source(t_disasm *disassm)
{
	disassm->header.prog_name[PROG_NAME_LENGTH] = '\0';
	disassm->header.comment[COMMENT_LENGTH] = '\0';
	write(disassm->fd_out, ".name \"", 7);
	ft_putstr_fd(disassm->header.prog_name, disassm->fd_out);
	write(disassm->fd_out, "\"\n", 2);
	write(disassm->fd_out, ".comment \"", 10);
	ft_putstr_fd(disassm->header.comment, disassm->fd_out);
	write(disassm->fd_out, "\"\n\n", 3);
	disassm->idx = 0;
	while (disassm->idx < disassm->header.prog_size)
		write_program(disassm);
	close(disassm->fd_out);
}
