/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 20:47:56 by laleta            #+#    #+#             */
/*   Updated: 2020/03/03 20:45:33 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_asm.h"

static int8_t	go_forward_str(t_inline *iline)
{
	if (!iline->len || iline->col > iline->len - 1)
		return (1);
	else
		iline->col++;
	return (0);
}

static int8_t	skip_insignificant_char(t_inline *iline)
{
	int8_t	stop;
	int32_t	seprtr_cnt;

	seprtr_cnt = 0;
	stop = 0;
	while (!stop && iline->str[iline->col] &&
									is_insignificant(iline->str[iline->col]))
	{
		if (iline->str[iline->col] == SEPARATOR_CHAR)
			seprtr_cnt++;
		stop = go_forward_str(iline);
	}
	if (seprtr_cnt > 1 || (seprtr_cnt < 1 && iline->col_alt == 2))
		return (0);
	return (1);
}

static char		*get_token_raw(t_inline *iline)
{
	uint64_t	start;
	int8_t		stop;

	stop = 0;
	if (!skip_insignificant_char(iline))
		return (NULL);
	if (!iline->str[iline->col] || !ft_isprint(iline->str[iline->col]))
		return (NULL);
	else
	{
		start = iline->col;
		while (!stop && iline->str[iline->col] &&
			iline->str[iline->col] != COMMENT_CMD_CHAR &&
			!(iline->col > 0 &&
			ft_strchr(LABEL_CHARS, iline->str[iline->col - 1]) &&
			(iline->str[iline->col] == LABEL_CHAR)) &&
			(!(iline->col != start && iline->col != start + 1 &&
			(iline->str[iline->col] == DIRECT_CHAR ||
			iline->str[iline->col] == '-' || iline->str[iline->col] == '+'))) &&
			(!is_insignificant(iline->str[iline->col])))
			stop = go_forward_str(iline);
		if (iline->str[iline->col] == LABEL_CHAR)
			iline->col++;
		return (ft_strsub(iline->str, start, iline->col - start));
	}
}

static void		get_token_type(t_token *token)
{
	token->subtype = 0;
	if (!token->raw)
	{
		token->type = ASM_EMPTY;
		token->subtype = ASM_EMPTY;
		return ;
	}
	if (is_header(token))
		token->type = ASM_HEADER;
	else if (is_label(token))
	{
		token->raw[ft_strlen(token->raw) - 1] = '\0';
		token->type = ASM_LABEL;
	}
	else if (is_operation(token))
		token->type = ASM_OPERATION;
	else if (is_argument(token))
		token->type = ASM_ARGUMENT;
	else
		token->type = ASM_UNDEF;
}

t_token			*get_token(t_asm *assm, t_inline *iline)
{
	t_token *token;

	if (!(token = (t_token *)malloc(sizeof(t_token))))
		error_handle(assm->file_name, ERR_MALLOC, assm, NULL);
	token->raw = NULL;
	token->raw = get_token_raw(iline);
	get_token_type(token);
	return (token);
}
