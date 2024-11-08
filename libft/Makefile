# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akastler <akastler@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 13:07:18 by akastler          #+#    #+#              #
#    Updated: 2022/11/18 09:41:49 by akastler         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_bzero.c		\
	  ft_isascii.c		\
	  ft_memchr.c		\
	  ft_memmove.c		\
	  ft_strlcat.c		\
	  ft_strncmp.c		\
	  ft_strjoin.c		\
	  ft_tolower.c		\
	  ft_isalnum.c		\
	  ft_isdigit.c		\
	  ft_memcmp.c		\
	  ft_memset.c		\
	  ft_substr.c		\
	  ft_strtrim.c		\
	  ft_strlcpy.c		\
	  ft_strnstr.c		\
	  ft_toupper.c		\
	  ft_atoi.c			\
	  ft_isalpha.c		\
	  ft_isprint.c		\
	  ft_memcpy.c		\
	  ft_strchr.c		\
	  ft_strlen.c		\
	  ft_strrchr.c		\
	  ft_calloc.c		\
	  ft_strdup.c		\
	  ft_split.c 		\
	  ft_itoa.c			\
	  ft_strmapi.c		\
	  ft_striteri.c		\
	  ft_putchar_fd.c	\
	  ft_putstr_fd.c 	\
	  ft_putendl_fd.c	\
	  ft_putnbr_fd.c	\

BONUS_SRC = ft_lstnew.c			\
			ft_lstadd_front.c	\
			ft_lstsize.c		\
			ft_lstlast.c		\
			ft_lstadd_back.c	\
			ft_lstdelone.c		\
			ft_lstclear.c		\
			ft_lstiter.c		\
			ft_lstmap.c			\

OBJS = ${SRC:.c=.o}

BONUS_OBJS = ${BONUS_SRC:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

AR = ar rcs

all: ${NAME}

${NAME}:	${OBJS}
	${AR} ${NAME} ${OBJS}

bonus: ${BONUS_OBJS}
	${AR} ${NAME} ${BONUS_OBJS}

clean:
	${RM} ${OBJS} ${BONUS_OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all
	
.PHONY: all clean fclean re bonus