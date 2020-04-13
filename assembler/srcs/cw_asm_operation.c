/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 18:20:23 by laleta            #+#    #+#             */
/*   Updated: 2020/02/20 21:05:09 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_asm.h"
#include "cw_asm_operation.h"

uint8_t	get_byte_size(t_token **argument, uint8_t arg_cnt, uint8_t type)
{
	uint8_t	size;
	uint8_t	i;

	i = 0;
	size = 0;
	size += OPER_SIZE;
	size += (g_oper_tab[type].is_arg_code ? ARGCODE_SIZE : 0);
	while (i < arg_cnt)
	{
		size += (argument[i]->subtype & T_DIR ? g_oper_tab[type].dir_size : 0);
		size += (argument[i]->subtype & T_REG ? REGNBR_SIZE : 0);
		size += (argument[i]->subtype & T_IND ? IND_SIZE : 0);
		i++;
	}
	return (size);
}

t_token	**get_argument(t_asm *assm, t_inline *iline, uint8_t arg_cnt,
																t_token *token)
{
	t_token **argument;
	uint8_t	i;

	i = 0;
	argument = (t_token **)ft_memalloc(sizeof(t_token *) * (arg_cnt + 1));
	while (i < arg_cnt)
	{
		if (i > 0)
			iline->col_alt = 2;
		argument[i] = get_token(assm, iline);
		if (argument[i]->type != ASM_ARGUMENT)
		{
			error_handle_adv2(assm, iline, ERR_ARGUMENT_INVALID, &argument[i]);
			token_arr_free(argument, i + 1);
			token_free(&token);
			exit(1);
		}
		i++;
	}
	iline->col_alt = 0;
	argument[i] = NULL;
	return (argument);
}

uint8_t	set_argcode(t_token **argument, uint8_t arg_cnt)
{
	uint8_t	arg_code;
	uint8_t subtype_code;
	int8_t	i;

	i = 0;
	arg_code = 0;
	while (i < 3)
	{
		if (i < arg_cnt && argument[i]->subtype == T_IND)
			subtype_code = IND_CODE;
		else if (i < arg_cnt)
			subtype_code = argument[i]->subtype;
		else
			subtype_code = 0;
		arg_code += (i < arg_cnt) ? subtype_code : 0;
		arg_code <<= 2;
		i++;
	}
	return (arg_code);
}

void	asm_operation(t_asm *assm, t_inline *iline, t_oper_queue *queue,
																t_token *token)
{
	t_token			**arg;
	t_node_queue	*node_queue;
	uint8_t			arg_code;
	uint8_t			bytes;
	uint8_t			i;

	i = 0;
	arg = get_argument(assm, iline, g_oper_tab[token->subtype].arg_cnt, token);
	while (i < g_oper_tab[token->subtype].arg_cnt)
	{
		if (!(arg[i]->subtype & g_oper_tab[token->subtype].arg_type[i]))
		{
			error_handle_adv2(assm, iline, ERR_ARGTYPE_INVALID, &arg[i]);
			token_arr_free(arg, g_oper_tab[token->subtype].arg_cnt);
			token_free(&token);
			exit(1);
		}
		i++;
	}
	arg_code = (!g_oper_tab[token->subtype].is_arg_code) ? 0 :
						set_argcode(arg, g_oper_tab[token->subtype].arg_cnt);
	bytes = get_byte_size(arg, g_oper_tab[token->subtype].arg_cnt,
																token->subtype);
	node_queue = operqueue_create_node(token->subtype, arg_code, bytes, arg);
	operqueue_push(assm, queue, node_queue);
}

void	operation_processing(t_asm *assm, t_token **token, t_inline *iline,
															char **label_str)
{
	if ((*token)->type == ASM_LABEL)
	{
		if (*label_str != NULL)
			labelist_push_back(assm, &assm->labels, label_str,
												assm->oper_queue->byte_total);
		*label_str = ft_strdup((*token)->raw);
		token_free(token);
		*token = get_token(assm, iline);
	}
	if ((*token)->type == ASM_OPERATION)
	{
		if (*label_str != NULL)
			labelist_push_back(assm, &assm->labels, label_str,
												assm->oper_queue->byte_total);
		asm_operation(assm, iline, assm->oper_queue, *token);
	}
	else if ((*token)->type != ASM_EMPTY)
	{
		ft_strdel(label_str);
		error_handle_adv(assm, iline, ERR_TOKEN_INVALID, token);
	}
}
