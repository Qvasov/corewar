NAME = ft_printf.a

FLAGS = -Wall -Wextra -Werror

DIR_S = src/
DIR_O = obj/

INCLUDES = ft_printf.h

SOURCES =	ft_printf.c\
            ft_sets.c\
          	ft_matching_format.c\
          	ft_matching_length.c\
            ft_matching_type.c\
            ft_printf_pointer.c\
            ft_printf_string.c\
            ft_printf_char.c\
            ft_printf_d_i_n_h_hh.c\
            ft_printf_d_i_u_ll.c\
            ft_printf_d_i_u_l.c\
            ft_printf_u_n_h_hh.c\
            ft_printf_o_n_h_hh.c\
            ft_printf_o_ll.c\
            ft_printf_o_l.c\
            ft_printf_xx_n_h_hh.c\
            ft_printf_x_n_h_hh.c\
            ft_printf_x_xx_ll.c\
            ft_printf_x_xx_l.c\
            ft_printf_b_l_ll.c\
            ft_printf_b_n_h_hh.c\
            ft_printf_percent.c\
            ft_buff_int.c\
            ft_set_hex_alpha.c\
            ft_buffering.c\
            ft_put_digit.c\
            ft_min_pow_array.c\
            ft_printf_lf.c\
            ft_printf_llf.c\
            ft_printf_e_ee_l_ll.c\
            ft_approx_double.c\
            ft_buff_double.c\
            ft_set_double_struct.c\
            ft_mult_sum_array.c\
            ft_fprint_not_format.c\
            ft_color.c\

SRCS = $(addprefix $(DIR_S),$(SOURCES))

OBJS = $(addprefix $(DIR_O),$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(DIR_O)%.o: %.c
	@mkdir -p $(DIR_O)
	gcc $(FLAGS) -I . -o $@ -c $<

clean:
	rm -rf $(DIR_O)

fclean: clean
	rm -f $(NAME)

re: fclean all
