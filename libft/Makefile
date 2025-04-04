# LIBFT Makefile

# List of source files for libft
SRCS = src/ft_atoi.c src/ft_isalpha.c src/ft_isdigit.c src/ft_memset.c src/ft_strlen.c

# Object files corresponding to the source files
OBJS = $(SRCS:.c=.o)

# Compiler and cleaning commands
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I. -I./includes


# The name of the static library
LIBFT = libft.a

# Default target
all: $(LIBFT)

# Rule to create the static library
$(LIBFT): $(OBJS)
	ar rcs $@ $^

# Rule to clean object files
clean:
	$(RM) $(OBJS)

# Rule to clean and remove the library
fclean: clean
	$(RM) $(LIBFT)

# Rule to rebuild everything
re: fclean all
