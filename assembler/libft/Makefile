# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laleta <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/07 19:28:58 by laleta            #+#    #+#              #
#    Updated: 2020/03/04 04:05:02 by laleta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror
SOURCE = ft_atoi.c ft_atoi_base.c ft_itoa.c ft_convert_base.c\
		ft_bzero.c ft_memalloc.c ft_memcmp.c ft_memcpy.c ft_memccpy.c\
		ft_memchr.c ft_memdel.c ft_memmove.c ft_memset.c\
		ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c\
		ft_putnbr.c ft_putnbr_fd.c ft_putnbr_base.c ft_putstr.c ft_putstr_fd.c\
		ft_strchr.c ft_strclr.c ft_strdup.c ft_strlen.c ft_strcat.c\
		ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strequ.c ft_strjoin.c\
		ft_strnequ.c ft_striter.c ft_striteri.c ft_strlcat.c ft_strlcpy.c\
		ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncpy.c ft_strncmp.c\
		ft_strnstr.c ft_strnew.c ft_strrchr.c ft_strstr.c ft_strtrim.c\
		ft_strsplit.c ft_strsub.c ft_swap.c ft_sqrt.c ft_ldiv.c\
		ft_isascii.c ft_isalpha.c ft_isalnum.c ft_isdigit.c ft_isprint.c\
		ft_isupper.c ft_toupper.c ft_tolower.c ft_lstnew.c\
		ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c\
		ft_sort_wordtab.c ft_print_wordtab.c ft_free_wordtab.c\
		get_next_line.c\
		gnl_strmerge.c gnl_clist_del_node.c gnl_clist_find_prev.c\
		gnl_clist_insert.c gnl_clist_new.c\
		ft_printf.c\
		pf_float.c pf_ftoa.c pf_itoa_base.c pf_dragon4.c pf_wctoa.c\
		pf_parse_ldouble.c pf_printf.c pf_type.c ft_fwrite.c\
		pf_putbuf.c pf_float_f.c pf_float_e.c ft_ceil.c pf_round_hex.c\
		pf_bigint_set.c pf_bigint_cmp_cpy_div.c pf_bigint_mul.c pf_bigint_pow.c\
		pf_bigint_shiftl.c pf_parse.c pf_type_num.c pf_type_str.c pf_time.c\
		

HEADER = libft.h ft_printf.h pf_buffer.h pf_design.h pf_dragon4.h pf_errno.h\
		pf_time.h pf_types.h get_next_line.h

INCLUDES = -Iincludes

VPATH = includes srcs srcs/ft_printf srcs/get_next_line

OBJECT = $(SOURCE:.c=.o)

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJECT)
	ar rc $@ $?
	ranlib $@

%.o : %.c $(HEADER)
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

clean :
	@rm -f $(OBJECT)

fclean : clean 
	@rm -f $(NAME)

re : fclean all
