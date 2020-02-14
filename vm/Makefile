# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laleta <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/07 19:28:58 by laleta            #+#    #+#              #
#    Updated: 2020/02/14 20:45:29 by laleta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar
FLAGS = -g
#-Wall -Wextra -Werror
SOURCE = ft_add_sub_and_or_xor.c ft_battle.c ft_checkout.c ft_copy_cursor.c\
		ft_create_buf.c ft_cycle.c ft_endgame.c ft_error.c ft_flags_check.c\
		ft_get.c ft_init_cursors.c ft_init_op.c ft_init_valid_func.c\
		ft_introducing.c ft_ld_ldi_lld_lldi.c ft_live_zjmp_fork_lfork_aff.c\
		ft_parse.c ft_print_commands.c ft_read_valid_players.c ft_st_sti.c\
		ft_usage.c ft_valid_op_code_and_reg.c main.c op.c\
		cw_visual_main.c cw_visual_cursor.c cw_visual_info.c\
		ft_free.c ft_visu_cursor.c ft_visu_cycle.c ft_visu_op.c ft_visu_init.c
HEADER = op.h vm.h cw_visual.h

INCLUDES = -Iinc -I$(LIBFT_DIR)

NCURSES_DIR = /Users/${USER}/.brew/Cellar/ncurses/6.1/

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = libft/

LIB = -lft -lncurses

LIB_DIR = -L$(LIBFT_DIR)

VPATH = src inc

OBJECT = $(SOURCE:.c=.o)

.PHONY : all clean fclean re install

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJECT)
	@echo "\033[1;3;34m"
	gcc $(FLAGS) $(OBJECT) -o $@ $(INCLUDES) $(LIB_DIR) $(LIB)
	@echo "\033[23;32m--[ "$(NAME) ]-- successfully compiled"\033[0m"

$(LIBFT) :
	@echo "\033[33;3m"
	@make -C $(LIBFT_DIR)
	@echo "\033[0m"

%.o : %.c $(HEADER)
	@echo "\033[36;3m"
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[0m"

clean :
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJECT)

fclean : clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re : fclean all

install:
	@if [ ! -d $(NCURSES_DIR) ] ; then brew install ncurses; fi
