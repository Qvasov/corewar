/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 01:11:12 by laleta            #+#    #+#             */
/*   Updated: 2019/06/23 23:57:04 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PF_TYPES_H
# define PF_TYPES_H

# include "ft_printf.h"

static t_types g_type_tab[] =
{
	{'c', &ft_type_c},
	{'C', &ft_type_c},
	{'d', &ft_type_d_i},
	{'D', &ft_type_d_i},
	{'i', &ft_type_d_i},
	{'o', &ft_type_o_u_x},
	{'O', &ft_type_o_u_x},
	{'u', &ft_type_o_u_x},
	{'U', &ft_type_o_u_x},
	{'x', &ft_type_o_u_x},
	{'X', &ft_type_o_u_x},
	{'b', &ft_type_o_u_x},
	{'B', &ft_type_o_u_x},
	{'e', &ft_type_e_f_g_a},
	{'E', &ft_type_e_f_g_a},
	{'f', &ft_type_e_f_g_a},
	{'F', &ft_type_e_f_g_a},
	{'g', &ft_type_e_f_g_a},
	{'G', &ft_type_e_f_g_a},
	{'a', &ft_type_e_f_g_a},
	{'A', &ft_type_e_f_g_a},
	{'n', &ft_type_n},
	{'p', &ft_type_p},
	{'s', &ft_type_s_r},
	{'S', &ft_type_s_r},
	{'r', &ft_type_s_r},
	{'R', &ft_type_s_r},
	{'m', &ft_type_m},
	{'M', &ft_type_m},
	{'k', &ft_type_k},
	{'K', &ft_type_k},
	{'%', &ft_type_proc},
	{'0', &ft_type_undef}
};

#endif
