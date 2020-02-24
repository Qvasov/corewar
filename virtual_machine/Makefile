# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laleta <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/07 19:28:58 by laleta            #+#    #+#              #
#    Updated: 2020/02/25 19:03:21 by laleta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE_DIR = ../
NAME = corewar
NAME_EXE = $(EXE_DIR)$(NAME)
FLAGS = -Wall -Wextra -Werror
SOURCE = cw_flag_v1_v2_v8_v16.c cw_flag_v4.c cw_visual_cursor.c \
 		cw_visual_info.c cw_visual_main.c cw_web_cur.c cw_web_cycle.c \
 		cw_web_init.c ft_battle.c ft_checkout.c ft_copy_cursor.c ft_cycle.c \
 		ft_endgame.c ft_error.c ft_flags_check.c ft_free.c ft_get.c \
 		ft_init_cursors.c ft_init_op.c ft_init_valid_func.c ft_introducing.c \
 		ft_op_add_sub_and_or_xor.c ft_op_ld_ldi_lld_lldi.c ft_op_st_sti.c\
 		ft_op_live_zjmp_fork_lfork_aff.c ft_parse.c ft_read_valid_players.c \
 		ft_usage.c ft_valid_op_code_and_reg.c main.c op.c
HEADER = op.h vm.h cw_visual.h types.h

INCLUDES = -Iinc -I$(LIBFT_DIR)

NCURSES_DIR = /Users/${USER}/.brew/Cellar/ncurses/6.1/

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = libft/

LIB = -lft -lncurses

LIB_DIR = -L$(LIBFT_DIR)

VPATH = src inc

OBJECT = $(SOURCE:.c=.o)

.PHONY : all clean fclean re install

all : $(NAME_EXE)

$(NAME_EXE) : $(LIBFT) $(OBJECT)
	@echo "\033[1;3;34m"
	gcc $(FLAGS) $(OBJECT) -o $@ $(INCLUDES) $(LIB_DIR) $(LIB)
	@echo "\033[23;32m--[ "$(NAME) ]-- successfully compiled"\033[0m"

$(LIBFT) :
	@echo "\033[33;3m"
	@make -C $(LIBFT_DIR)
	@echo "\033[0m"

%.o : %.c $(HEADER)
	@echo "\033[36;3m\c"
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[0m\c"

clean :
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJECT)

fclean : clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME_EXE)

re : fclean all

install:
	@if [ ! -d $(NCURSES_DIR) ] ; then brew install ncurses; fi
