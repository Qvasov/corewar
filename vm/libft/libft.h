/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:44:20 by ddarell           #+#    #+#             */
/*   Updated: 2020/01/21 20:00:29 by ddarell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include "ft_printf/ft_printf.h"

# define GNL_BUFF_SIZE  4
# define MAX_FD 10240

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
								size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char*));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstaddback(t_list **alst, t_list *new);
void				ft_bclean(char **s, int i);
void				ft_matrixclr(char **matrix, size_t matrix_size);
int					ft_lstcount(t_list *list);
void				ft_sort_int_tab(int *tab, size_t size);
void				ft_int_swap(int *a, int *b);
void				ft_str_swap(char **a, char **b);
int					ft_max(int a, int b);
void				ft_reverse_str(char *str);
char				*ft_strcapitalize(char *str);
int					ft_atoi_spec(const char *str);
int					ft_bit_check(int flag, int position);
void				ft_bit_on(int *flag, int position);
void				ft_bit_off(int *flag, int position);
int					ft_seach_min_int(int *tab, int size);
int					ft_search_int_tab(int *tab, int size, int num);
long long			ft_atoll(const char *str);
unsigned long long	ft_atoull(const char *str);
char				*ft_lltoa(long long n);
void				ft_putchar_buf(char *buf, size_t *i,
								size_t buff_size, char c);
void				ft_putnbr_buf(char *buf, size_t *i,
								size_t buff_size, int num);
void				ft_putstr_buf(char *buf, size_t *i,
								size_t buff_size, char *str);
int					ft_satoi(const char *str, int *i);
int					ft_seach_min_int(int *tab, int size);
int					ft_strchr_count(const char *s, int c);
void				ft_strrev(char *str);
void				ft_swapptr(void **a, void **b);
char				*ft_ulltoa(unsigned long long n);

#endif
