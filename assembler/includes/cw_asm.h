/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 04:17:43 by laleta            #+#    #+#             */
/*   Updated: 2020/03/14 16:38:35 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_ASM_H
# define CW_ASM_H

# include "libft.h"
# include "cw_asm_op.h"
# include "cw_asm_error.h"
# include "cw_disasm.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>

# define MAX_FILE_PATH		128
# define ASM_UNDEF			0
# define ASM_LABEL			1
# define ASM_OPERATION		2
# define ASM_ARGUMENT		3
# define ASM_HEADER			4
# define ASM_EMPTY			-1
# define NAME_HEAD			1
# define COMMENT_HEAD		2
# define OPER_SIZE			1
# define ARGCODE_SIZE		1

# define CL_ER				"\033[37;41;1m"
# define CL_OK				"\033[37;42;1m"
# define CL_INFO			"\033[34;1m"

extern uint8_t			g_disasm;

typedef	struct			s_token
{
	int8_t				type;
	uint8_t				subtype;
	char				*raw;
}						t_token;

typedef	struct			s_inline
{
	uint64_t			len;
	uint64_t			col;
	uint64_t			col_alt;
	uint64_t			row;
	char				*str;
}						t_inline;

typedef struct			s_label
{
	char				*raw;
	uint64_t			hash;
	uint16_t			byte_start;
	struct s_label		*next;
}						t_label;

typedef struct			s_node_queue
{
	t_token				**argument;
	uint8_t				oper_id;
	uint8_t				arg_code;
	uint8_t				bytes;
	struct s_node_queue	*next;
}						t_node_queue;

typedef struct			s_oper_queue
{
	t_node_queue		*first;
	t_node_queue		*last;
	uint32_t			byte_total;
	uint16_t			oper_cnt;
}						t_oper_queue;

typedef struct			s_asm
{
	int32_t				fd_in;
	int32_t				fd_out;
	char				*path_file_name;
	char				*file_name;
	t_header			*header;
	t_label				*labels;
	t_oper_queue		*oper_queue;
}						t_asm;

typedef struct			s_operation
{
	char				*name;
	uint8_t				arg_cnt;
	uint8_t				arg_type[3];
	uint8_t				is_arg_code;
	uint8_t				dir_size;
}						t_operation;

void					file_handle(t_asm *assm);
void					asm_init(t_asm **assm, char *file_name, int32_t fd);
void					asm_free(t_asm *assm);
char					*del_comment(char **str, uint8_t pos);
t_token					*get_token(t_asm *assm, t_inline *iline);
void					token_free(t_token **token);
void					token_arr_free(t_token **token_arr, uint8_t cnt);
void					node_queue_free(t_node_queue *node);
int8_t					is_header(t_token *token);
int8_t					is_label(t_token *token);
int8_t					is_operation(t_token *token);
int8_t					is_argument(t_token *token);
int8_t					is_register(t_token *token);
int8_t					is_direct(t_token *token);
int8_t					is_indirect(t_token *token);
int8_t					is_insignificant(int32_t c);
void					header_processing(t_asm *assm, t_token **token,
													t_inline *iline, char **s);
void					operation_processing(t_asm *assm, t_token **token,
											t_inline *iline, char **label_str);
void					labelist_push_back(t_asm *assm, t_label **labelist,
											char **str, uint32_t byte_start);
void					labelist_free(t_label **labelist);
uint16_t				labelist_search(t_asm *assm, t_label *labelist,
										t_node_queue *node, const char *str);
uint64_t				get_hash(const char *str);
t_node_queue			*operqueue_create_node(uint8_t oper_type,
							uint8_t arg_code, uint8_t byte_size, t_token **arg);
void					operqueue_push(t_asm *assm, t_oper_queue *queue,
															t_node_queue *node);
t_node_queue			*operqueue_pop(t_oper_queue *queue);
int8_t					operqueue_is_empty(t_oper_queue *queue);
void					operqueue_free(t_oper_queue *queue);
void					translate_to_bytecode(t_asm *assm);
void					error_handle(const char *name, const char *err_str,
											t_asm *assm, t_disasm *disassm);
void					error_handle2(const char *name, const char *err_str,
											t_asm *assm, t_disasm *disassm);
void					error_handle_adv(t_asm *assm, t_inline *iline,
										const char *err_str, t_token **token);
void					error_handle_adv2(t_asm *assm, t_inline *iline,
										const char *err_str, t_token **token);
#endif
