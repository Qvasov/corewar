/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_file_handle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 00:17:29 by laleta            #+#    #+#             */
/*   Updated: 2020/02/25 14:28:25 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_asm.h"

static char	*get_earlier_ptr(char *p1, char *p2)
{
	if (p1 && p2)
	{
		if (p1 <= p2)
			return (p1);
		else
			return (p2);
	}
	else
	{
		if (p1 >= p2)
			return (p1);
		else
			return (p2);
	}
	return (p1);
}

char		*del_comment(char **str, uint8_t pos)
{
	char	*com_ptr;
	char	*com_ptr_alt;
	char	*search_ptr;
	char	*quot_ptr;
	char	*res;

	quot_ptr = NULL;
	search_ptr = NULL;
	com_ptr = ft_strchr(*str, COMMENT_CHAR);
	com_ptr_alt = ft_strchr(*str, COMMENT_CHAR_ALT);
	com_ptr = get_earlier_ptr(com_ptr, com_ptr_alt);
	if ((quot_ptr = ft_strchr(*str, COMMENT_CMD_CHAR)) != NULL)
		search_ptr = ft_strchr(quot_ptr + 1, COMMENT_CMD_CHAR);
	if (quot_ptr != NULL && quot_ptr < com_ptr)
	{
		if (pos == 2)
			search_ptr = quot_ptr;
		com_ptr = ft_strchr(search_ptr, COMMENT_CHAR);
		com_ptr_alt = ft_strchr(search_ptr, COMMENT_CHAR_ALT);
		com_ptr = get_earlier_ptr(com_ptr, com_ptr_alt);
	}
	res = (com_ptr && pos != 0) ? ft_strsub(*str, 0, com_ptr - *str) :
																ft_strdup(*str);
	ft_strdel(str);
	return (res);
}

static char	*file_parse(t_asm *assm, t_inline *iline, t_token *token)
{
	char	*str_in;
	char	*label_str;

	str_in = NULL;
	label_str = NULL;
	while (get_next_line(assm->fd_in, &str_in) > 0)
	{
		iline->str = del_comment(&str_in, 1);
		iline->len = ft_strlen(iline->str);
		token = get_token(assm, iline);
		header_processing(assm, &token, iline, &label_str);
		if (iline->str[iline->col] == ',')
			error_handle_adv(assm, iline, ERR_EXTRA_CHAR, NULL);
		token_free(&token);
		token = get_token(assm, iline);
		if (token->type != ASM_EMPTY)
			error_handle_adv(assm, iline, ERR_EXTRA_TOKEN, token->raw);
		token_free(&token);
		ft_strdel(&iline->str);
		iline->row++;
		iline->col = 0;
	}
	return (label_str);
}

void		file_handle(t_asm *assm)
{
	char		*label_str;
	t_inline	iline;
	t_token		*token;

	token = NULL;
	iline.col = 0;
	iline.row = 1;
	label_str = NULL;
	label_str = file_parse(assm, &iline, token);
	if (label_str)
		labelist_push_back(assm, &assm->labels, &label_str,
												assm->oper_queue->byte_total);
	if (assm->oper_queue->byte_total == 0)
		error_handle(assm->file_name, ERR_NO_OPERATION, assm, NULL);
	assm->header->prog_size = assm->oper_queue->byte_total;
}
