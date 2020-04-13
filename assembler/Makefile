# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laleta <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/07 19:28:58 by laleta            #+#    #+#              #
#    Updated: 2020/03/04 04:04:46 by laleta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE_DIR = ../
NAME = asm
NAME_EXE = $(EXE_DIR)$(NAME)
FLAGS = -Wall -Wextra -Werror
SOURCE = cw_asm_main.c cw_asm_file_handle.c cw_asm_init_free.c cw_asm_header.c\
		cw_asm_token.c cw_asm_token_type.c cw_asm_token_type2.c\
		cw_asm_label_list.c cw_asm_operation.c cw_asm_oper_queue.c\
		cw_asm_bytecode.c cw_asm_error.c cw_asm_util.c\
		cw_disasm_init_free.c cw_disasm_file_handle.c cw_disasm_source.c
HEADER = cw_asm_op.h cw_asm.h cw_asm_error.h cw_asm_hash.h cw_asm_operation.h\
		cw_disasm.h

INCLUDES = -Iincludes -I$(LIBFT_DIR)includes

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = libft/

LIB = -lft

LIB_DIR = -L$(LIBFT_DIR)

VPATH = srcs includes

OBJECT = $(SOURCE:.c=.o)

.PHONY : all clean fclean re

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
