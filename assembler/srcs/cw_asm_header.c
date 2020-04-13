/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:58:56 by laleta            #+#    #+#             */
/*   Updated: 2020/03/14 16:35:25 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_asm.h"

static void	check_header(t_asm *assm, t_inline *iline, int k, t_token **token)
{
	uint64_t i;

	i = 0;
	while (iline->str[i] == ' ' || iline->str[i] == '\t')
		i++;
	i += k;
	while (iline->str[i] != COMMENT_CMD_CHAR)
	{
		if (iline->str[i] != ' ' && iline->str[i] != '\t')
		{
			ft_strdel(&iline->str);
			token_free(token);
			error_handle(assm->file_name, ERR_HEADER_EXTRA_CHAR, assm, NULL);
		}
		i++;
	}
}

static void	get_header_inner(t_asm *assm, t_inline **iline, t_token **token,
																	uint64_t l)
{
	char		*str_in;
	char		*str_raw;
	char		*quot_ptr;

	str_raw = NULL;
	quot_ptr = NULL;
	while (!(*iline)->col_alt && get_next_line(assm->fd_in, &str_raw) > 0)
	{
		str_in = !ft_strchr(str_raw, COMMENT_CMD_CHAR) ?
						del_comment(&str_raw, 0) : del_comment(&str_raw, 2);
		l = ft_strlen((*iline)->str);
		(*iline)->str = (char *)realloc((*iline)->str, ft_strlen(str_in) + l +
																			2);
		(*iline)->str[l] = '\n';
		ft_strncpy(&((*iline)->str[l + 1]), str_in, ft_strlen(str_in) + 1);
		(*iline)->row++;
		(*iline)->len = ft_strlen((*iline)->str);
		if ((quot_ptr = ft_strchr(str_in, COMMENT_CMD_CHAR)) != NULL)
			(*iline)->col_alt = quot_ptr - str_in + 1;
		ft_strdel(&str_in);
	}
	ft_strdel(&str_raw);
	ft_strdel(&str_in);
	if (quot_ptr == NULL)
		error_handle_adv(assm, *iline, ERR_HEADER_UNFINISH, token);
}

static void	get_header_name(t_asm *assm, t_inline *iline, t_token **token)
{
	char		*start_ptr;
	char		*end_ptr;
	char		*tmp;

	if (!(start_ptr = ft_strchr(iline->str, COMMENT_CMD_CHAR)))
		error_handle_adv(assm, iline, ERR_NAME_MISSING, token);
	if (!(end_ptr = ft_strchr(start_ptr + 1, COMMENT_CMD_CHAR)))
		get_header_inner(assm, &iline, token, 0);
	if (end_ptr == NULL)
	{
		start_ptr = ft_strchr(iline->str, COMMENT_CMD_CHAR);
		end_ptr = ft_strchr(start_ptr + 1, COMMENT_CMD_CHAR);
	}
	check_header(assm, iline, ft_strlen(NAME_CMD_STRING), token);
	tmp = ft_strsub(iline->str, start_ptr + 1 - iline->str,
													end_ptr - start_ptr - 1);
	if (ft_strlen(tmp) > PROG_NAME_LENGTH)
	{
		ft_strdel(&tmp);
		error_handle_adv(assm, iline, ERR_NAME_LENGTH, token);
	}
	ft_strcpy(assm->header->prog_name, tmp);
	iline->col = (end_ptr - iline->str + 1);
	ft_strdel(&tmp);
}

static void	get_header_comment(t_asm *assm, t_inline *iline, t_token **token)
{
	char		*start_ptr;
	char		*end_ptr;
	char		*tmp;

	if (!(start_ptr = ft_strchr(iline->str, COMMENT_CMD_CHAR)))
		error_handle_adv(assm, iline, ERR_COMMENT_MISSING, token);
	if (!(end_ptr = ft_strchr(start_ptr + 1, COMMENT_CMD_CHAR)))
		get_header_inner(assm, &iline, token, 0);
	if (end_ptr == NULL)
	{
		start_ptr = ft_strchr(iline->str, COMMENT_CMD_CHAR);
		end_ptr = ft_strchr(start_ptr + 1, COMMENT_CMD_CHAR);
	}
	check_header(assm, iline, ft_strlen(COMMENT_CMD_STRING), token);
	tmp = ft_strsub(iline->str, start_ptr + 1 - iline->str,
													end_ptr - start_ptr - 1);
	if (ft_strlen(tmp) > COMMENT_LENGTH)
	{
		ft_strdel(&tmp);
		error_handle_adv(assm, iline, ERR_COMMENT_LENGTH, token);
	}
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
			error_handle_adv(assm, iline, ERR_NAME_REDEFINE, token);
		get_header_name(assm, iline, token);
		header_flag |= NAME_HEAD;
	}
	else if ((*token)->type == ASM_HEADER && (*token)->subtype == COMMENT_HEAD)
	{
		if (header_flag & COMMENT_HEAD)
			error_handle_adv(assm, iline, ERR_COMMENT_REDEFINE, token);
		get_header_comment(assm, iline, token);
		header_flag |= COMMENT_HEAD;
	}
	else if ((*token)->type != ASM_EMPTY)
		error_handle_adv(assm, iline, ERR_TOKEN_INVALID, token);
}
