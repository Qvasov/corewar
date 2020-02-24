/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_token_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 21:09:37 by laleta            #+#    #+#             */
/*   Updated: 2020/02/03 20:00:44 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_asm.h"
#include "cw_asm_operation.h"

int8_t	is_header(t_token *token)
{
	if (*(token->raw) && *(token->raw) == '.')
	{
		if (ft_strequ(token->raw, NAME_CMD_STRING))
		{
			token->subtype = NAME_HEAD;
			return (1);
		}
		else if (ft_strequ(token->raw, COMMENT_CMD_STRING))
		{
			token->subtype = COMMENT_HEAD;
			return (1);
		}
	}
	return (0);
}

int8_t	is_label(t_token *token)
{
	uint64_t	i;
	uint64_t	len;

	len = ft_strlen(token->raw);
	i = 0;
	if (len > 1 && token->raw[len - 1] == LABEL_CHAR)
	{
		while (i < len - 1)
		{
			if (!ft_strchr(LABEL_CHARS, token->raw[i]))
				return (0);
			i++;
		}
		token->subtype = ASM_LABEL;
		return (1);
	}
	return (0);
}

int8_t	is_operation(t_token *token)
{
	uint8_t	i;

	i = 1;
	while (g_oper_tab[i].name[0])
	{
		if (ft_strequ(token->raw, g_oper_tab[i].name))
		{
			token->subtype = i;
			return (1);
		}
		i++;
	}
	return (0);
}

int8_t	is_argument(t_asm *assm, t_token *token, t_inline *iline)
{
	if (is_register(assm, token->raw, iline))
	{
		token->subtype = T_REG;
		return (1);
	}
	else if (is_direct(assm, token->raw, iline))
	{
		token->subtype = T_DIR;
		return (1);
	}
	else if (is_indirect(assm, token->raw, iline))
	{
		token->subtype = T_IND;
		return (1);
	}
	else
		return (0);
}
