# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qdenizar <qdenizar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/13 12:03:18 by akastler          #+#    #+#              #
#    Updated: 2023/07/06 17:56:42 by qdenizar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c main2.c init_struct.c history.c \
		./utils/utils.c ./utils/utils2.c ./utils/utils3.c ./utils/utils4.c \
		./utils/utils5.c  ./utils/utils6.c  ./utils/utils7.c  ./utils/utils8.c \
		./utils/utils9.c ./utils/utils10.c ./utils/utils11.c \
		./builtin/cd.c ./builtin/echo.c ./builtin/export.c ./builtin/env.c \
		./builtin/export2.c  ./builtin/export3.c \
		./builtin/exit.c ./builtin/pwd.c ./builtin/unset.c \
		./builtin/check_builtin.c ./builtin/check_builtin_helper.c \
		./parsing/parsing.c ./parsing/parsing2.c  ./parsing/parsing3.c \
		./parsing/parsing4.c  ./parsing/parsing5.c ./parsing/parsing6.c \
		./parsing/parsing7.c\
		./pipe/pipe.c init_struct2.c \
		signal.c redirection.c  redirection2.c \
		./cmd/cmd.c ./cmd/cmd2.c  ./cmd/cmd3.c ./cmd/pipes.c\


CC = gcc -Wall -Wextra -Werror -g3

RM = rm -rf

AR = ar rcs

INC = -I /Users/$$USER/.brew/opt/readline/include

LIBS = libft/libft.a get_next_line/gnl.a

LIB	= -lcurses -lreadline -L/Users/$$USER/.brew/opt/readline/lib

OBJS = ${SRCS:.c=.o}

.c.o:
	${CC} ${INC} -g3 -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	@make all -C ./libft
	@make all -C ./get_next_line
	@echo "libs compileded!"
	$(CC) $(OBJS) $(LIB) $(LIBS) -o $(NAME)
	@echo "minishell compileded!"

new_history:
	$(RM) .history
	@touch .history

re: fclean all

debug: $(OBJS)
	@make all -C ./libft
	@make all -C ./get_next_line
	@echo "libs compileded!"
	$(CC) $(DEBUG) $(OBJS) $(LIB) $(LIBS) -o $(NAME)
	@echo "minishell_debug compileded!"

clean:
	$(RM) $(OBJS)
	@echo "Minishell cleaned"

fclean:
	$(RM) $(OBJS) $(NAME)
	@echo "Minishell fcleaned"

clean_libs:
	@make clean -C ./libft
	@make clean -C ./get_next_line
	@echo "Librairies cleaned"

fclean_libs:
	@make fclean -C ./libft
	@make fclean -C ./get_next_line
	@echo "Librairies fcleaned"

clean_all: clean clean_libs

fclean_all: fclean fclean_libs

.PHONY: all clean fclean debug clean_libs fclean_libs clean_all fclean_all