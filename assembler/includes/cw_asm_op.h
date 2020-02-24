/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_op.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 05:38:43 by laleta            #+#    #+#             */
/*   Updated: 2020/02/24 13:17:29 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_ASM_OP_H
# define CW_ASM_OP_H

# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			4
# define REGNBR_SIZE		1
# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3
# define MAX_ARGS_NUMBER	4
# define MAX_PLAYERS		4
# define MEM_SIZE			4096
# define IDX_MOD			512
# define CHAMP_MAX_SIZE		682
# define COMMENT_CHAR		'#'
# define COMMENT_CHAR_ALT	';'
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','
# define REGISTER_CHAR		'r'
# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"
# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"
# define REG_NUMBER			16
# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10
# define T_REG				1
# define T_DIR				2
# define T_IND				4
# define T_LAB				8
# define PROG_NAME_LENGTH	128
# define COMMENT_LENGTH		2048
# define COREWAR_EXEC_MAGIC	0xea83f3
# define HEADER_SIZE 		2192
# define REGISTER_STR		"r"
# define DIRECT_STR			"%"
# define COMMENT_CMD_CHAR	'\"'

typedef char		t_arg_type;

typedef	struct		s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

#endif
