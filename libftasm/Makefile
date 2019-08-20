# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cobecque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/17 17:21:49 by cobecque          #+#    #+#              #
#    Updated: 2019/08/18 11:53:41 by cobecque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftasm.a

INC_NAME = ./../includes
SRC_NAME = ft_puts.s\
			ft_strlen.s\
			ft_bzero.s\
			ft_isalpha.s\
			ft_isdigit.s\
			ft_isalnum.s\
			ft_isascii.s\
			ft_isprint.s\
			ft_tolower.s\
			ft_toupper.s\
			ft_strcat.s\
			ft_memset.s\
			ft_memcpy.s\
			ft_strdup.s\
			ft_cat.s\
			ft_putnbr.s\
			ft_memalloc.s\
			ft_strncmp.s\
			ft_strndup.s

SRC_DIR = ./src
OBJ_DIR = ./obj

SRC_PATH = $(addprefix $(SRC_DIR)/,$(SRC_NAME))
OBJ_PATH = $(addprefix $(OBJ_DIR)/,$(SRC_NAME:.s=.o))

CC = nasm
FLAGS = -f macho64

all :
	@mkdir -p ./obj
	@$(MAKE) $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.s
	@$(CC) $(FLAGS) -I $(INC_NAME) -o $@ $<
	@printf $(C_BLU) "        [ ✔ ] $<"

$(NAME): $(OBJ_PATH)
	@ar -q $(NAME) $(OBJ_PATH) 2>/dev/null
	@printf $(C_CYA) "        [ ✔ ] compiled -> $(NAME)"

clean :
	@rm -rf $(OBJ_DIR)
	@/bin/rm -f $(OBJ_PATH)

fclean : clean
	@/bin/rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re

# color
C_RED = "\e[31;m%s\e[0n\n"
C_GRN = "\e[32;m%s\e[0n\n"
C_YEL = "\e[33;m%s\e[0n\n"
C_BLU = "\e[34;m%s\e[0n\n"
C_MAG = "\e[35;m%s\e[0n\n"
C_CYA = "\e[36;m%s\e[0n\n"

# color + \n
CN_RED = "\e[31;m%s\e[0n\n\n"
CN_GRN = "\e[32;m%s\e[0n\n\n"
CN_YEL = "\e[33;m%s\e[0n\n\n"
CN_BLU = "\e[34;m%s\e[0n\n\n"
CN_MAG = "\e[35;m%s\e[0n\n\n"
CN_CYA = "\e[36;m%s\e[0n\n\n"

