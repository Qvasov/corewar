/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2013/11/06 14:21:46 by zaz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include <stdint.h>

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				4096
# define IDX_MOD				512
# define CHAMP_MAX_SIZE			682

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		128
# define COMMENT_LENGTH			2048
# define COREWAR_EXEC_MAGIC		0xea83f3

# define ZERO					0x00
# define LIVE					0x01
# define LD						0x02
# define ST						0x03
# define ADD					0x04
# define SUB					0x05
# define AND					0x06
# define OR						0x07
# define XOR					0x08
# define ZJMP					0x09
# define LDI					0x0a
# define STI					0x0b
# define FORK					0x0c
# define LLD					0x0d
# define LLDI					0x0e
# define LFORK					0x0f
# define AFF					0x10

typedef struct		s_op
{
	char			*name;
	int8_t			args_count;
	uint8_t			arg_type[4];
	int8_t			code;
	int16_t			cycles;
	char			*comment;
	int8_t			args_type_code;
	int8_t			dir_size;
}					t_op;

#endif
