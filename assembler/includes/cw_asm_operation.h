/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_operation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 19:58:58 by laleta            #+#    #+#             */
/*   Updated: 2020/02/24 13:00:58 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_ASM_OPERATION_H
# define CW_ASM_OPERATION_H

# include "cw_asm.h"

static t_operation g_oper_tab[] =
{
	{"", 0, {0}, 0, 0},
	{"live", 1, {T_DIR}, 0, 4},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 1, 4},
	{"st", 2, {T_REG, T_IND | T_REG}, 1, 4},
	{"add", 3, {T_REG, T_REG, T_REG}, 1, 4},
	{"sub", 3, {T_REG, T_REG, T_REG}, 1, 4},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
	{"zjmp", 1, {T_DIR}, 0, 2},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 1, 2},
	{"fork", 1, {T_DIR}, 0, 2},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 1, 4},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
	{"lfork", 1, {T_DIR}, 0, 2},
	{"aff", 1, {T_REG}, 1, 4},
	{"", 0, {0}, 0, 0}
};

static t_argument	g_arg_type[] =
{
	{0, 0, ""},
	{T_REG, REGNBR_SIZE, REGISTER_STR},
	{T_DIR, DIR_SIZE, DIRECT_STR},
	{T_IND, IND_SIZE, ""}
};

#endif
