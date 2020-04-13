/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_token_type2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 20:35:28 by laleta            #+#    #+#             */
/*   Updated: 2020/03/14 16:36:21 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_asm.h"

int8_t	is_register(t_token *token)
{
	uint64_t	len;
	int32_t		nbr_reg;

	len = ft_strlen(token->raw);
	if ((len > 1) && token->raw[0] == REGISTER_CHAR)
	{
		nbr_reg = ft_atoi(&token->raw[1]);
		if (nbr_reg >= 1 && nbr_reg <= 99)
			return (1);
	}
	return (0);
}

int8_t	is_direct(t_token *token)
{
	uint64_t	len;
	uint64_t	i;

	i = 1;
	len = ft_strlen(token->raw);
	if (len > 2 && token->raw[0] == DIRECT_CHAR && token->raw[1] == LABEL_CHAR)
		return (1);
	else if (len > 1 && token->raw[0] == DIRECT_CHAR)
	{
		if (token->raw[i] == '+')
			return (0);
		if (token->raw[i] == '-')
			i++;
		while (token->raw[i])
		{
			if (!ft_isdigit(token->raw[i]))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int8_t	is_indirect(t_token *token)
{
	uint64_t	len;
	uint64_t	i;

	i = 0;
	len = ft_strlen(token->raw);
	if (len > 1 && token->raw[0] == LABEL_CHAR)
		return (1);
	if (len > 0)
	{
		if (token->raw[0] == '+')
			return (0);
		if (len > 1 && (token->raw[0] == '-'))
			i++;
		while (token->raw[i])
		{
			if (!ft_isdigit(token->raw[i]))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
