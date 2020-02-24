/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:58:56 by laleta            #+#    #+#             */
/*   Updated: 2020/02/25 17:14:55 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_asm.h"

static void	check_header(t_asm *assm, t_inline *iline, int k)
{
	uint64_t i;

	i = 0;
	while (iline->str[i] == ' ' || iline->str[i] == '\t')
		i++;
	i += k;
	while (iline->str[i] != '\"')
	{
		if (iline->str[i] != ' ' && iline->str[i] != '\t')
			error_handle(assm->file_name, ERR_HEADER_NULL, assm, NULL);
		i++;
	}
}

static void	get_header_inner(t_asm *assm, t_inline **iline, uint64_t l1,
																	uint64_t l2)
{
	char		*str_in;
	char		*str_raw;
	char		*quot_ptr;

	str_raw = NULL;
	quot_ptr = NULL;
	while (get_next_line(assm->fd_in, &str_raw) > 0)
	{
		str_in = !ft_strchr(str_raw, '"') ? del_comment(&str_raw, 0) :
													del_comment(&str_raw, 2);
		ft_strdel(&str_raw);
		l1 = ft_strlen((*iline)->str);
		l2 = ft_strlen(str_in);
		(*iline)->str = (char *)realloc((*iline)->str, sizeof(char) *
																(l1 + l2 + 2));
		(*iline)->str[l1] = '\n';
		ft_strncpy(&((*iline)->str[l1 + 1]), str_in, l2 + 1);
		(*iline)->row++;
		if ((quot_ptr = ft_strchr(str_in, '"')) != NULL)
			break ;
		ft_strdel(&str_in);
	}
	ft_strdel(&str_raw);
	if (quot_ptr == NULL)
		error_handle_adv(assm, *iline, ERR_NAME_UNFINISH, NULL);
}

static void	get_header_name(t_asm *assm, t_inline *iline)
{
	uint64_t	len;
	char		*start_ptr;
	char		*end_ptr;
	char		*tmp;

	if (!(start_ptr = ft_strchr(iline->str, '"')))
		error_handle_adv(assm, iline, ERR_NAME_MISSING, NULL);
	if (!(end_ptr = ft_strchr(start_ptr + 1, '"')))
		get_header_inner(assm, &iline, 0, 0);
	if (end_ptr == NULL)
	{
		start_ptr = ft_strchr(iline->str, '"');
		end_ptr = ft_strchr(start_ptr + 1, '"');
	}
	tmp = ft_strsub(iline->str, start_ptr + 1 - iline->str,
													end_ptr - start_ptr - 1);
	len = ft_strlen(tmp);
	check_header(assm, iline, 5);
	if (len > PROG_NAME_LENGTH)
		error_handle_adv(assm, iline, ERR_NAME_LENGTH, NULL);
	ft_strcpy(assm->header->prog_name, tmp);
	iline->col = (end_ptr - iline->str + 1);
	ft_strdel(&tmp);
}

static void	get_header_comment(t_asm *assm, t_inline *iline)
{
	uint64_t	len;
	char		*start_ptr;
	char		*end_ptr;
	char		*tmp;

	if (!(start_ptr = ft_strchr(iline->str, '"')))
		error_handle_adv(assm, iline, ERR_COMMENT_MISSING, NULL);
	if (!(end_ptr = ft_strchr(start_ptr + 1, '"')))
		get_header_inner(assm, &iline, 0, 0);
	if (end_ptr == NULL)
	{
		start_ptr = ft_strchr(iline->str, '"');
		end_ptr = ft_strchr(start_ptr + 1, '"');
	}
	tmp = ft_strsub(iline->str, start_ptr + 1 - iline->str,
													end_ptr - start_ptr - 1);
	len = ft_strlen(tmp);
	check_header(assm, iline, 8);
	if (len > COMMENT_LENGTH)
		error_handle_adv(assm, iline, ERR_COMMENT_LENGTH, NULL);
	ft_strcpy(assm->header->comment, tmp);
	iline->col = (end_ptr - iline->str + 1);
	ft_strdel(&tmp);
}

void		header_processing(t_asm *assm, t_token **token, t_inline *iline,
															char **label_str)
{
	static int8_t	header_flag = 0;

	if (iline->row == 1)
		header_flag = 0;
	if (header_flag == 3)
	{
		operation_processing(assm, token, iline, label_str);
		return ;
	}
	if ((*token)->type == ASM_HEADER && (*token)->subtype == NAME_HEAD)
	{
		if (header_flag & NAME_HEAD)
			error_handle_adv(assm, iline, ERR_NAME_REDEFINE, (*token)->raw);
		get_header_name(assm, iline);
		header_flag |= NAME_HEAD;
	}
	else if ((*token)->type == ASM_HEADER && (*token)->subtype == COMMENT_HEAD)
	{
		if (header_flag & COMMENT_HEAD)
			error_handle_adv(assm, iline, ERR_COMMENT_REDEFINE, (*token)->raw);
		get_header_comment(assm, iline);
		header_flag |= COMMENT_HEAD;
	}
	else if ((*token)->type != ASM_EMPTY)
		error_handle_adv(assm, iline, ERR_TOKEN_INVALID, (*token)->raw);
}
