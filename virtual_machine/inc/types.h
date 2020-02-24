/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbennie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 20:07:10 by dbennie           #+#    #+#             */
/*   Updated: 2020/02/24 20:07:11 by dbennie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>

# define INT_SIZE	4

typedef struct	s_visu
{
	int			fd;
	int			**curs;
	uint64_t	*arena;
	int64_t		*change;
	int			f;
}				t_visu;

typedef union	u_bits
{
	struct		s_bits
	{
		uint8_t bit0 : 1;
		uint8_t bit1 : 1;
		uint8_t bit2 : 1;
		uint8_t bit3 : 1;
	}			b;
	uint8_t		num;
}				t_bits;

typedef union	u_types_code
{
	struct		s_types_code
	{
		uint8_t	arg4 : 2;
		uint8_t	arg3 : 2;
		uint8_t	arg2 : 2;
		uint8_t	arg1 : 2;
	}			a;
	uint8_t		num;
}				t_types_code;

typedef union	u_int
{
	char		byte[INT_SIZE];
	int			num;
}				t_int;

#endif
