/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_token_type2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 20:35:28 by laleta            #+#    #+#             */
/*   Updated: 2020/02/20 18:19:01 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_asm.h"

int8_t	is_register(t_asm *assm, char *str, t_inline *iline)
{
	uint64_t	len;
	int32_t		nbr_reg;

	len = ft_strlen(str);
	if ((len > 1) && str[0] == REGISTER_CHAR)
	{
		nbr_reg = ft_atoi(&str[1]);
		if (nbr_reg >= 1 && nbr_reg <= 99)
			return (1);
		else
			error_handle_adv(assm, iline, ERR_REG_NBR, str);
	}
	return (0);
}

int8_t	is_direct(t_asm *assm, char *str, t_inline *iline)
{
	uint64_t	len;
	uint64_t	i;

	i = 1;
	len = ft_strlen(str);
	if (len > 2 && str[0] == DIRECT_CHAR && str[1] == LABEL_CHAR)
		return (1);
	else if (len > 1 && str[0] == DIRECT_CHAR)
	{
		if (str[i] == '+')
			error_handle_adv(assm, iline, ERR_ARGUMENT_INVALID, str);
		if (str[i] == '-')
			i++;
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
				error_handle_adv(assm, iline, ERR_ARGUMENT_INVALID, str);
			i++;
		}
		return (1);
	}
	return (0);
}

int8_t	is_indirect(t_asm *assm, char *str, t_inline *iline)
{
	uint64_t	len;
	uint64_t	i;

	i = 0;
	len = ft_strlen(str);
	if (len > 1 && str[0] == LABEL_CHAR)
		return (1);
	if (len > 0)
	{
		if (str[0] == '+')
			error_handle_adv(assm, iline, ERR_ARGUMENT_INVALID, str);
		if (len > 1 && (str[0] == '-'))
			i++;
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
				error_handle_adv(assm, iline, ERR_ARGUMENT_INVALID, str);
			i++;
		}
		return (1);
	}
	return (0);
}
