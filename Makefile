NAME =			michel
TEST_BIN =		minishell_test
CC =			gcc
AR =			ar rcs
CFLAGS =		-g
LIBFT_DIR =		includes/libft
LIBFT =			$(LIBFT_DIR)/libft.a
PRINTF_DIR =	includes/ft_printf
PRINTF =		$(PRINTF_DIR)/libftprintf.a

SRC =			src/main.c \

CORE =			src/core/env/expansion/expansion.c \
				src/core/env/getters/list_env.c \
				src/core/env/getters/list_export.c \
				src/core/env/getters/merge_sort.c \
				src/core/env/initialization/cleaner.c \
				src/core/env/initialization/cloners.c \
				src/core/env/initialization/helpers.c \
				src/core/env/initialization/initializer.c \
				src/core/env/setters/helpers.c \
				src/core/env/setters/setter.c \
				src/core/env/setters/unset.c \
				src/core/shell_loop/loop.c \
				src/core/program/cleaner.c \
				src/core/program/initializer.c \
				src/core/program/program.c \
				src/core/signals/signals.c \

# HELPERS	=		src/helpers/ft_split.c \
				src/helpers/ft_split_helper.c \
				src/helpers/maintester.c

PARSER = 		src/lexer/parser/parser.c \
				src/lexer/parser/cleaner.c \
				src/lexer/tokenizer/expansion.c \
				src/lexer/tokenizer/tokenization.c \
				src/lexer/tokenizer/helpers.c \
				src/lexer/tokenizer/operator_parser.c \
				src/lexer/tokenizer/quote_parser.c \
				src/lexer/tokenizer/word_parser.c \
				

SIGNALS = 		
				
UTILS = 		src/utils/utils1.c \

TEST_SRC =		src/non_interactive_minishell.c \
				src/core/non_interactive_minishell/program.c \

OBJS =			$(SRC:.c=.o) $(CORE:.c=.o) $(PARSER:.c=.o) $(HELPERS:.c=.o) $(SIGNALS:.c=.o) $(UTILS:.c=.o)

TEST_OBJS =		$(TEST_SRC:.c=.o) $(CORE:.c=.o) $(PARSER:.c=.o) $(HELPERS:.c=.o) $(SIGNALS:.c=.o) $(UTILS:.c=.o)

all :			$(NAME)

$(NAME) :		$(OBJS) $(LIBFT) $(PRINTF)
				@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME) -lreadline
# $(CC) $(OBJS) -lreadline -LLibft -lft -o ${NAME}

tester:			$(TEST_BIN)

$(TEST_BIN) :	$(TEST_OBJS) $(LIBFT) $(PRINTF)
				@$(CC) $(CFLAGS) $(TEST_OBJS) $(LIBFT) $(PRINTF) -o $(TEST_BIN) -lreadline

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

tclean:			clean fclean
				@rm -f $(TEST_BIN) $(BONUS)
				@make --no-print-directory fclean -C $(LIBFT_DIR)
				@make --no-print-directory fclean -C $(PRINTF_DIR)

re :			fclean all
te :			fclean tclean tester
