NAME=minishell
CC=gcc
CFLAGS= #-Wall -Werror -Wextra
SRCS= $(shell find ./srcs -name "*.c" -type f 2> /dev/null)
LIBFT= -L./libft/ -I./libft/ -lft

OBJ=$(SRCS:.c=.o)

RM=rm -rf

# Color
RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
MAGENTA=\033[1;35m
RESET=\033[0m

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	LREAD_DIR = -L/usr/local/lib -I/usr/local/include/ -lreadline
else 
	LREAD_DIR = -L/usr/local/opt/readline -I/usr/local/opt/readline/include -lreadline
endif

INC=-iquote./inc $(LREAD_DIR) $(LIBFT)

all:$(NAME)

%.o:%.c libft
	@echo "$(GREEN)Compile $(BLUE)$<$(RESET)"
	@$(CC) $(CFLAGS) -iquote./inc -c $< -o $@ -g

$(NAME):$(OBJ)
	@echo "$(GREEN)Compile $(RESET)$(BLUE)$(NAME)$(RESET)"
	@printf "$(RED)$(SEP)\nCOMPILE STATEMENT\n$(SEP)\n"
	-$(CC) $(CFLAGS) $(OBJ) $(INC) -o $(NAME)
	@printf "$(RED)\n$(SEP)\n$(RESET)"
	@echo "$(GREEN)Done$(RESET)"

libft:
	@echo "Start Create $(BLUE)Lib-ft$(RESET)"
	@make --no-print-directory -C ./libft

clean:
	@make --no-print-directory -C ./libft clean
	@$(RM) $(OBJ)
	@$(RM) *.dSYM

fclean: clean
	@make --no-print-directory -C ./libft fclean
	@ echo "$(RED)Remove Libft $(RESET)"
	@$(RM) $(NAME)
	@echo "$(RED)Remove minishell $(RESET)"

re: fclean all

SEP="----------------------------------------"

.PHONY: all libft clean fclean re
