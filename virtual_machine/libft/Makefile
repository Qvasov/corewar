# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbennie <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/09 17:34:33 by dbennie           #+#    #+#              #
#    Updated: 2019/10/30 21:45:38 by dbennie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c\
      	ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c\
      	ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_lstmap.c\
      	ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c\
      	ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c\
      	ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c\
      	ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c\
      	ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c\
      	ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
      	ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c\
      	ft_strnstr.c ft_lstaddback.c ft_bclean.c ft_matrixclr.c ft_lstcount.c\
      	ft_sort_int_tab.c ft_int_swap.c ft_str_swap.c ft_max.c ft_reverse_str.c\
      	ft_strcapitalize.c ft_atoi_spec.c ft_bit.c\
      	ft_search_min_int.c ft_search_int_tab.c ft_atoll.c ft_atoull.c ft_lltoa.c\
      	ft_putchar_buf.c ft_putnbr_buf.c ft_putstr_buf.c ft_satoi.c ft_strrev.c\
      	ft_strchr_count.c ft_swapptr.c ft_ulltoa.c\

PRINTF = ft_printf/

INC = libft.h

DIR_O = obj/

OBJS = $(addprefix $(DIR_O),$(SRC:.c=.o))

HEADO = libft.h.gch

CC = gcc

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(PRINTF)
	cp ft_printf/ft_printf.a $(NAME)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(DIR_O)%.o: $(DIR_S)%.c
	@mkdir -p $(DIR_O)
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	rm -rf $(DIR_O)
	make clean -C $(PRINTF)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(PRINTF)

re: fclean all
