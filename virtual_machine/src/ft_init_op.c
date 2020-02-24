/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:18:08 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/25 14:18:09 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_init_op(void (**op) (t_data *, t_cur *))
{
	op[0] = NULL;
	op[1] = live;
	op[2] = ld;
	op[3] = st;
	op[4] = add;
	op[5] = sub;
	op[6] = and;
	op[7] = or;
	op[8] = xor;
	op[9] = zjmp;
	op[10] = ldi;
	op[11] = sti;
	op[12] = fork_cw;
	op[13] = lld;
	op[14] = lldi;
	op[15] = lfork_cw;
	op[16] = aff;
}
