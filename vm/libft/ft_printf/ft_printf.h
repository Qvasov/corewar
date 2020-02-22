/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:00:49 by ddarell           #+#    #+#             */
/*   Updated: 2020/02/21 14:14:31 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_PRINTF_H
# define _FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>

# define BUF_SIZE 32786

# define MINUS 0
# define PLUS 1
# define SPACE 2
# define NOLL 3
# define HASH 4

# define LONG_DOUBLE 8
# define LONG_LONG 9
# define LONG 10
# define SHORT 11
# define SHORT_SHORT 12

# define TYPE 16
# define IFG_NUM 5

# define DEC 10
# define DEC_LL 19
# define DEC_ULL 20
# define DEC_L 19
# define DEC_UL 20
# define DEC_H 5
# define DEC_HH 3

# define OCT 11
# define OCT_LL 22
# define OCT_L 22
# define OCT_H 6
# define OCT_HH 3

# define HEX 8
# define HEX_LL 16
# define HEX_L 16
# define HEX_H 4
# define HEX_HH 2

# define BIN 32
# define BIN_LL 64
# define BIN_L 64
# define BIN_H 16
# define BIN_HH 8

# define D_LIMIT_E 752
# define D_LIMIT_M 16

# define LD_LIMIT_E 11495
# define LD_LIMIT_M 20

typedef struct			s_ldbl
{
	unsigned long long	lull;
	unsigned int		li;
}						t_ldbl;

typedef union			u_udbl
{
	double				lf;
	unsigned long long	ull;
	long double			llf;
	t_ldbl				ldbl;
}						t_udbl;

typedef struct			s_dbl
{
	t_udbl				udbl;
	char				sign;
	char				point;
	int					ord;
	int					exc;
	int					len;
	char				*res;
}						t_dbl;

typedef union			u_union
{
	int					in;
	long int			lin;
	long long int		llin;
	unsigned int		uin;
	unsigned long int	ulin;
	unsigned long long	ullin;
}						t_union;

typedef struct			s_fstr
{
	int					idx;
	int					prin;
	int					flag;
	int					wdth;
	int					prec;
	int					strl;
	int					sfd;
	t_union				uni;
	char				buf[BUF_SIZE];
}						t_fstr;

int						ft_printf(const char *format, ...);
int						ft_fprintf(int fd, const char *format, ...);
int						ft_bprintf(t_fstr *fstr, const char *format, ...);

void					ft_set_fstr(t_fstr *fstr);
void					ft_init_f(void (**f)(t_fstr *, va_list *));
void					ft_init_fstr(t_fstr *fstr);

int						ft_print_not_format(char *format, t_fstr *fstr);
int						ft_fprint_not_format(char *format, t_fstr *fstr);

int						ft_match_type(t_fstr *fstr, char *current);
int						ft_match_flags(t_fstr *fstr, char *current);
int						ft_match_width(t_fstr *fstr, char *current,
										va_list *arg);
int						ft_match_prec(t_fstr *fstr, char *current,
										va_list *arg);
int						ft_match_length(t_fstr *fstr, char *current);

int						ft_flag(int flag, int position);

int						ft_put_digit_dec(char *dig, unsigned int a, int size);
int						ft_put_digit_oct(char *dig, unsigned int a, int size);
int						ft_put_digit_hex(char *dig, unsigned int a,
											int size, char *base);
int						ft_put_digit_hex_ll(char *dig, unsigned long long int a,
											int size, char *base);
int						ft_put_digit_bin(char *dig, unsigned int a, int size);

void					ft_printf_char(t_fstr *fstr, va_list *arg);
void					ft_printf_string(t_fstr *fstr, va_list *arg);
void					ft_printf_percent(t_fstr *fstr, va_list *arg);
void					ft_printf_pointer(t_fstr *fstr, va_list *arg);

void					ft_printf_d_i(t_fstr *fstr, va_list *arg);
void					ft_printf_d_i_ll(t_fstr *fstr, va_list *arg);
void					ft_printf_d_i_l(t_fstr *fstr, va_list *arg);
void					ft_printf_d_i_h(t_fstr *fstr, va_list *arg);
void					ft_printf_d_i_hh(t_fstr *fstr, va_list *arg);
void					ft_printf_u(t_fstr *fstr, va_list *arg);
void					ft_printf_u_ll(t_fstr *fstr, va_list *arg);
void					ft_printf_u_l(t_fstr *fstr, va_list *arg);
void					ft_printf_u_h(t_fstr *fstr, va_list *arg);
void					ft_printf_u_hh(t_fstr *fstr, va_list *arg);
void					ft_printf_o(t_fstr *fstr, va_list *arg);
void					ft_printf_o_ll(t_fstr *fstr, va_list *arg);
void					ft_printf_o_l(t_fstr *fstr, va_list *arg);
void					ft_printf_o_h(t_fstr *fstr, va_list *arg);
void					ft_printf_o_hh(t_fstr *fstr, va_list *arg);
void					ft_printf_xx(t_fstr *fstr, va_list *arg);
void					ft_printf_xx_ll(t_fstr *fstr, va_list *arg);
void					ft_printf_xx_l(t_fstr *fstr, va_list *arg);
void					ft_printf_xx_h(t_fstr *fstr, va_list *arg);
void					ft_printf_xx_hh(t_fstr *fstr, va_list *arg);
void					ft_printf_x(t_fstr *fstr, va_list *arg);
void					ft_printf_x_ll(t_fstr *fstr, va_list *arg);
void					ft_printf_x_l(t_fstr *fstr, va_list *arg);
void					ft_printf_x_h(t_fstr *fstr, va_list *arg);
void					ft_printf_x_hh(t_fstr *fstr, va_list *arg);
void					ft_printf_b(t_fstr *fstr, va_list *arg);
void					ft_printf_b_ll(t_fstr *fstr, va_list *arg);
void					ft_printf_b_l(t_fstr *fstr, va_list *arg);
void					ft_printf_b_h(t_fstr *fstr, va_list *arg);
void					ft_printf_b_hh(t_fstr *fstr, va_list *arg);

void					ft_printf_f_l(t_fstr *fstr, va_list *arg);
void					ft_printf_f_ll(t_fstr *fstr, va_list *arg);
void					ft_printf_e_ee_l(t_fstr *fstr, va_list *arg);
void					ft_printf_e_ee_ll(t_fstr *fstr, va_list *arg);

void					ft_print_str_width(t_fstr *fstr, int l);

void					ft_print_int_width(t_fstr *fstr, char *sign, int w);
void					ft_print_int_prec(t_fstr *fstr, char *sign, int len);
void					ft_check_ox(t_fstr *fstr, char *sign, char flag);
void					ft_set_sign_x(t_fstr *fstr, char *sign);
void					ft_set_sign_xx(t_fstr *fstr, char *sign);

void					ft_check_double_sign_n_prec(t_fstr *fstr, t_dbl *dbl,
													unsigned int sign_bit);
int						ft_check_double_width_n_point(t_fstr *fstr, t_dbl *dbl);
void					ft_check_double_exc(int expo_flag,
											unsigned long long int mant,
											t_fstr *fstr, t_dbl *dbl);
void					ft_dtoa_to_array(t_dbl *dbl, int exp,
											unsigned long long mnt);
void					ft_ldtoa_to_array(t_dbl *dbl, int exp,
											unsigned long long mnt);
void					ft_approx_double(char *res, t_dbl *dbl, int prec);
void					ft_buff_double_width(t_fstr *fstr, char *sign, int len);
void					ft_buff_double(t_fstr *fstr, char *res, t_dbl *dbl);

void					ft_pow_to_array(char *buf, int ground, int pow);
int						ft_bin_pow_array(char *buf, int e);
int						ft_rev_mult_array_num(char *buf,
												unsigned long long int num);
int						ft_rev_sum_array_array(char *res, char *arr);

void					ft_buf_smb(char smb, int size, t_fstr *fstr);
void					ft_buf_str(char *str, int size, t_fstr *fstr);
void					ft_buf_str_full(char *str, int size, t_fstr *fstr);
void					ft_buf_print(t_fstr *fstr);

int						ft_check_color(char *format, t_fstr *fstr);

#endif
