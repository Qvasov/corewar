/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:59:59 by laleta            #+#    #+#             */
/*   Updated: 2020/02/17 20:58:46 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_DISASM_H
# define CW_DISASM_H

# include "cw_asm_op.h"
# include <stdint.h>

typedef struct	s_disasm
{
	uint64_t	idx;
	int32_t		fd_out;
	char		*file_name;
	char		*path_file_name;
	t_header	header;
	uint8_t		program[CHAMP_MAX_SIZE];
}				t_disasm;

typedef struct	s_argument
{
	uint8_t		code;
	uint8_t		size;
	char		*str;
}				t_argument;

void			disasm_init(t_disasm **disassm, char *file_name);
void			disasm_file_handle(t_disasm *disassm, int32_t fd);
void			translate_to_source(t_disasm *disassm);
void			disasm_free(t_disasm *disassm);
uint16_t		swap_byte2(uint16_t nbr);
uint32_t		swap_byte4(uint32_t nbr);
uint8_t			get_bits(uint8_t i, uint8_t arg_code);

#endif
