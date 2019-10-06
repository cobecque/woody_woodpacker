# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cobecque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/18 11:55:23 by cobecque          #+#    #+#              #
#    Updated: 2019/10/01 07:21:35 by cobecque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors.

ORANGE =	\033[1;33m   #It is actually Yellow, but i changed yellow to orange.

GREEN =		\033[1;32m

RED =		\033[1;31m

RES =		\033[0m

#------------------------------------------------------------------------------#

NAME = 		woody_woodpacker

SRCDIR =	./src

OBJDIR =	./obj

INCDIR =	./includes

# List all sources, objects and includes files of 'libft'.

SRC =	main.c \
	fill_struc.c \
	section.c

INC =	woody.h

SRCS =		$(SRC:%=$(SRCDIR)/%)

OBJS =		$(SRC:%.c=$(OBJDIR)/%.o)

INCS =		$(INC:%=$(INCDIR)/%)

LIBDIR =	./libft
LIBPDIR =	./libft/src/printf
LIBADIR =	./libftasm

LIBNAME =	libft.a
LIBPNAME =	libftprintf.a
LIBANAME = libftasm.a

LIB =		$(LIBDIR)/$(LIBNAME)
LIBP =		$(LIBPDIR)/$(LIBPNAME)
LIBA = 		$(LIBADIR)/$(LIBANAME)

#------------------------------------------------------------------------------#
# List all compilation variables.

CC =		gcc

CFLAGS =	-Wall			\
			-Wextra			\
			-Werror			\

INCFLAGS =	-I $(INCDIR)

LFLAGS =	-L $(LIBDIR) -l$(LIBNAME:lib%.a=%) -L $(LIBPDIR) -l$(LIBPNAME:lib%.a=%) -L $(LIBADIR) -l$(LIBANAME:lib%.a=%)

FLAGS =		$(CFLAGS)		\
			$(INCFLAGS)

#------------------------------------------------------------------------------#
# List all rules used to make libft.a

all:
	@$(MAKE) -C $(LIBADIR)
	@$(MAKE) -C $(LIBPDIR)
	@$(MAKE) $(NAME)

$(NAME): $(OBJS) $(LIB)
	@$(MAKE) printname
	@printf "%-15s%s\n" Linking $@
	@$(CC) $(FLAGS) $^ -o $@ $(LFLAGS)
	@printf "$(GREEN)"
	@echo "Compilation done !"
	@printf "$(RES)"

$(OBJS): $(INCS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(MAKE) printname
	@printf "%-15s%s\n" Compiling $@
	@$(CC) $(FLAGS) -o $@ -c -fPIC $<

printname:
	@printf "$(ORANGE)"
	@printf "[%-15s " "$(NAME)]"
	@printf "$(RES)"

clean:
	@$(MAKE) printname
	@echo Suppressing obj files
	@printf "$(RED)"
	@rm -rf $(OBJS)
	@rm -rf $(OBJDIR)
	@printf "$(RES)"

fclean: clean
	@make fclean -C $(LIBPDIR)
	@make fclean -C $(LIBADIR)
	@$(MAKE) printname
	@rm -rf ./woody
	@echo Suppressing $(NAME)
	@printf "$(RED)"
	rm -rf $(NAME)
	@printf "$(RES)"

re: fclean
	@$(MAKE) all

#------------------------------------------------------------------------------#
# List of all my optionnals but usefull rules.

NORM = `norminette $(SRCS) $(INCS) | grep -B1 Error | cat`

norm:
	@$(MAKE) printname
	@echo "Passage de la norminette :"
	@if [ "$(NORM)" == "`echo ""`" ];									\
		then															\
			echo "$(GREEN)Tous les fichiers sont a la norme !$(RES)";	\
		else															\
			echo "$(RED)$(NORM)$(RES)";									\
	fi

check:
	#@$(MAKE) -C $(LIBDIR) check
	@$(MAKE) norm

# A rule to make git add easier

git:
	@$(MAKE) -C $(LIBPDIR) git
	@$(MAKE) printname
	@echo Adding files to git repository
	@printf "$(GREEN)"
	git add $(SRCS) $(INCS) Makefile
	@printf "$(RES)"
	git status

.PHONY: all clean re fclean git norm check
