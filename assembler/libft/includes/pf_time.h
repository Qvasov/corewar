/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_time.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 05:52:51 by laleta            #+#    #+#             */
/*   Updated: 2020/02/24 16:43:30 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PF_TIME_H
# define PF_TIME_H

# include <time.h>
# include <stdint.h>

typedef	struct			s_tim
{
	int16_t				sec;
	int16_t				min;
	int16_t				hour;
	int16_t				day;
	int16_t				mon;
	int32_t				year;
}						t_tim;

static const int32_t	g_lmos[] =
{
	0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335
};
static const int32_t	g_mos[] =
{
	0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
};

void					ft_ttoa(char **buf);

#endif
