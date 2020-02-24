/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 03:51:59 by laleta            #+#    #+#             */
/*   Updated: 2019/07/01 04:00:30 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include "pf_dragon4.h"
# include "pf_design.h"
# include "pf_buffer.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

# define F_SP		0x01
# define F_PL		0x02
# define F_MI		0x04
# define F_PO		0x08
# define F_ZE		0x10
# define INT_MAX	2147483647
# define UINT_MAX	4294967295
# define INF		1
# define NAN		2
# define POINT		'.'

typedef struct		s_wr_fun
{
	void	*(*f)(void *, const char *, size_t);
	void	*arg;
}					t_wr_fun;

typedef struct		s_prnf
{
	union
	{
		int64_t		i;
		long double	f;
	}				nbr;
	char			*s;
	int32_t			n0;
	int32_t			nz0;
	int32_t			n1;
	int32_t			nz1;
	int32_t			n2;
	int32_t			nz2;
	int32_t			prec;
	int64_t			width;
	int64_t			nchar;
	uint32_t		flags;
	char			size;
	char			size2;
	char			size3;
	char			size4;
}					t_prnf;

typedef struct		s_types
{
	char			type;
	void			(*f)(char, char *, t_prnf *, va_list *);
}					t_types;

int32_t				ft_printf(const char *fmt, ...);
int32_t				ft_fprintf(int32_t fd, const char *fmt, ...);
int32_t				ft_sprintf(char *s, const char *fmt, ...);
int32_t				ft_prnf(t_wr_fun *wr, const char *fmt, va_list *ap,
																	t_prnf *pf);
void				ft_parse_fmt_specfr(t_prnf *pf, const char **s,
																va_list *ap);
int32_t				ft_putbuf(t_prnf *pf, va_list *ap, char type, char *buf);
void				ft_round_hex(t_prnf *pf, char *num, char type);
void				ft_gen_ftype(t_prnf *pf, char type, char *buf, int16_t *ed);
void				ft_gen_f(t_prnf *pf, char type, char *buf, int16_t *ed);
void				ft_gen_e(t_prnf *pf, char type, char *buf, int16_t *ed);
void				ft_ftoa(t_prnf *pf, char type);
void				ft_ftoa_hex(t_prnf *pf, char type, int16_t i);
void				ft_itoa_base(t_prnf *pf, char type);
void				ft_wctoa(t_prnf *pf, unsigned int *wc, char type);
int16_t				ft_get_inf_nan(long double *num);
void				ft_get_exp_mant(long double *nu, int32_t *exp, uint64_t *m);
void				ft_put_exp(t_prnf *pf, char type, char *buf, int16_t exp);
size_t				ft_fwrite(const void *ptr, size_t s, size_t nel, t_file *f);
int32_t				ft_fflush(t_file *str);
uint32_t			dragon4(char *buf, t_bigint *bigints, long double *num,
															int32_t *exp_out);
void				ft_type_d_i(char type, char *buf, t_prnf *pf, va_list *ap);
void				ft_type_c(char type, char *buf, t_prnf *pf, va_list *ap);
void				ft_type_o_u_x(char typ, char *buf, t_prnf *pf, va_list *ap);
void				ft_type_e_f_g_a(char tp, char *buf, t_prnf *pf, va_list *a);
void				ft_type_n(char type, char *buf, t_prnf *pf, va_list *ap);
void				ft_type_p(char type, char *buf, t_prnf *pf, va_list *ap);
void				ft_type_s_r(char type, char *buf, t_prnf *pf, va_list *ap);
void				ft_type_m(char type, char *buf, t_prnf *pf, va_list *ap);
void				ft_type_k(char type, char *buf, t_prnf *pf, va_list *ap);
void				ft_type_r(char type, t_prnf *pf, int32_t i, int32_t j);
void				ft_type_proc(char type, char *buf, t_prnf *pf, va_list *ap);
void				ft_type_undef(char typ, char *buf, t_prnf *pf, va_list *ap);

#endif
