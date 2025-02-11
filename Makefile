NAME =			minishell
CC =			gcc
AR =			ar rcs
CFLAGS =		-g
LIBFT_DIR =		includes/libft
LIBFT =			$(LIBFT_DIR)/libft.a
PRINTF_DIR =	includes/ft_printf
PRINTF =		$(PRINTF_DIR)/libftprintf.a

SRC =			src/main.c \

CORE =			src/core/environment_variables/cleaner.c \
				src/core/environment_variables/cloner.c \
				src/core/environment_variables/helpers.c \
				src/core/environment_variables/initializer.c \
				src/core/shell_loop/loop.c \
				src/core/program/program.c \
				src/core/program/cleaner.c \
				src/core/signals/signals.c \

# HELPERS	=		src/helpers/ft_split.c \
				src/helpers/ft_split_helper.c \
				src/helpers/maintester.c

PARSER = 		src/parser/parser.c \
				

SIGNALS = 		
				
UTILS = 		src/utils/utils1.c \

OBJS =			$(SRC:.c=.o) $(CORE:.c=.o) $(PARSER:.c=.o) $(HELPERS:.c=.o) $(SIGNALS:.c=.o) $(UTILS:.c=.o)

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
