NAME =		libft.a
CC =		gcc
CFLAGS =	-Wall -Wextra -Werror
RM =		@rm -f

SRCS =		ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_is_only_whitespace.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdelimiter.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_itoa.c \
			ft_lstadd_front_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstnew_bonus.c \
			ft_lstsize_bonus.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putchar.c \
			ft_putendl_fd.c \
			ft_puthex.c \
			ft_putnbr_fd.c \
			ft_putnbr.c \
			ft_putptr.c \
			ft_putstr_fd.c \
			ft_putstr.c \
			ft_putunbr.c \
			ft_realloc.c \
			ft_split_charset.c \
			ft_strcasecmp.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strndup.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtok.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_substring.c \
			ft_tolower.c \
			ft_toupper.c \

OBJS =		$(SRCS:.c=.o)

all: $(NAME)

$(NAME):	$(OBJS)
			@ar rcs $(NAME) $(OBJS)

%.o:		%.c
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all