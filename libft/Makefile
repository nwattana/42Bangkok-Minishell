# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nwattana <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 00:39:59 by nwattana          #+#    #+#              #
#    Updated: 2023/02/19 11:59:38 by nwattana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
      ft_toupper.c ft_tolower.c ft_strlen.c \
      ft_atoi.c ft_bzero.c ft_calloc.c \
      ft_memcpy.c ft_memset.c ft_memmove.c \
      ft_strlcpy.c ft_strlcat.c ft_strchr.c \
      ft_strrchr.c ft_memchr.c ft_memcmp.c \
      ft_strnstr.c ft_strdup.c ft_strncmp.c \
      ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
      ft_itoa.c ft_putnbr_fd.c ft_substr.c \
      ft_strjoin.c ft_strappend.c ft_strtrim.c \
      ft_split.c ft_striteri.c ft_strmapi.c \
	  ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
	  ft_lstlast.c ft_lstdelone.c ft_lstclear.c \
	  ft_lstadd_back.c ft_lstiter.c ft_lstmap.c \
	  ft_stack_push.c ft_stack_pop.c ft_stack_init.c \
	  ft_stack_clear.c ft_stack_peak.c ft_strcmp.c

GREEN=\033[1;32m
RESET=\033[0m

OBJS = $(SRC:.c=.o)

NAME = libft.a
CC = gcc
CC_FLAG = -Wall -Wextra -Werror

all: ${NAME}

%.o: %.c
	@${CC} ${CC_FLAG} -c $< -o $@ -g
	@echo "$(GREEN).$(RESET)\c"


$(NAME): ${OBJS}
	@ar -rcs ${NAME} ${OBJS}
	@echo "\n$(GREEN)LIBFT CREATE DONE$(RESET)"

norm:
	@norminett *.c

clean:
	@rm -f *.o

fclean: clean
	@rm -f ${NAME}

re:fclean all

.PHONY:norm all clean fclean re 
