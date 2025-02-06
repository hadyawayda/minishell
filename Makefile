NAME =			minishell
CC =			gcc
AR =			ar rcs
CFLAGS =		-g
LIBFT_DIR =		includes/libft
LIBFT =			$(LIBFT_DIR)/libft.a
PRINTF_DIR =	includes/ft_printf
PRINTF =		$(PRINTF_DIR)/libftprintf.a

HELPERS	=		src/helpers/ft_split.c \
				src/helpers/ft_split_helper.c
				# src/helpers/maintester.c \

BUILT_INS = 	src/builtins/ft_echo.c \
				src/builtins/ft_pwd.c \
				src/builtins/ft_exit.c \
				src/builtins/ft_cd.c \

SIGNALS = 		src/signals/signals.c \
				
UTILS = 		src/utils/utils1.c \

SRC =			src/main.c \

OBJS =			$(SRC:.c=.o) $(HELPERS:.c=.o) $(SIGNALS:.c=.o) $(BUILT_INS:.c=.o) $(UTILS:.c=.o)

all :			$(NAME)

$(NAME) :		$(OBJS) $(LIBFT) $(PRINTF)
				@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME) -lreadline
# $(CC) $(OBJS) -lreadline -LLibft -lft -o ${NAME}

$(LIBFT):
				@make --no-print-directory -C $(LIBFT_DIR)

$(PRINTF):		$(LIBFT)
				@make --no-print-directory -C $(PRINTF_DIR)

%.o :			%.c
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@rm -f ${OBJS} $(BONUS_OBJ)
				@make --no-print-directory clean -C $(LIBFT_DIR)
				@make --no-print-directory clean -C $(PRINTF_DIR)

fclean:			clean
				@rm -f $(NAME) $(BONUS)
				@make --no-print-directory fclean -C $(LIBFT_DIR)
				@make --no-print-directory fclean -C $(PRINTF_DIR)

re :			fclean all
