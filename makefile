# List of source files
# List of source files
SRCS = src/main.c src/shell.c src/utils/utils.c \
       src/builtins/echo.c src/builtins/cd.c src/builtins/cd_utils.c \
       src/builtins/pwd.c src/builtins/exit.c \
       src/builtins/env.c src/builtins/export.c \
       src/builtins/export_2.c

# Object files
OBJS = $(SRCS:.c=.o)

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft

# Libraries
LIBFT = libft/includes/libft.a
LIBS = -Llibft -lft -lreadline

# Final executable
NAME = minishell

# Build rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -o $(NAME) $(LIBS)

# Build libft if necessary
$(LIBFT):
	make -C libft

# Clean rules
clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
