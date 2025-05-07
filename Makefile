NAME =			michel
CC =			gcc
AR =			ar rcs
CFLAGS =		-g
LIBFT_DIR =		includes/libft
LIBFT =			$(LIBFT_DIR)/libft.a
PRINTF_DIR =	includes/ft_printf
PRINTF =		$(PRINTF_DIR)/libftprintf.a
SUPPRESSION =	includes/utils/ignore_readline.supp

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

LEXER = 		src/lexer/parser/ast_builder.c \
				src/lexer/parser/ast_traverser.c \
				src/lexer/parser/heredoc.c \
				src/lexer/parser/parser_utils.c \
				src/lexer/parser/parser.c \
				src/lexer/parser/syntax_checker.c \
				src/lexer/parser/tree_visualizer.c \
				src/lexer/tokenizer/dollar_parser.c \
				src/lexer/tokenizer/expansion.c \
				src/lexer/tokenizer/tokenization.c \
				src/lexer/tokenizer/helpers.c \
				src/lexer/tokenizer/operator_parser.c \
				src/lexer/tokenizer/quote_parser.c \
				src/lexer/tokenizer/word_parser.c \

OBJDIR =		includes/objs

SRCS =			$(SRC) $(CORE) $(LEXER)

OBJS =			$(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

all :			$(NAME)

$(NAME) :		$(OBJS) $(LIBFT) $(PRINTF)
				@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $@ -lreadline

$(LIBFT):
				@make --no-print-directory -C $(LIBFT_DIR)

$(PRINTF):		$(LIBFT)
				@make --no-print-directory -C $(PRINTF_DIR)

$(OBJDIR)/%.o:	%.c
				@mkdir -p $(dir $@)
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@rm -f ${OBJS} $(BONUS_OBJ)
				@make --no-print-directory clean -C $(LIBFT_DIR)
				@make --no-print-directory clean -C $(PRINTF_DIR)

fclean:			clean
				@rm -f $(NAME) $(BONUS)
				@make --no-print-directory fclean -C $(LIBFT_DIR)
				@make --no-print-directory fclean -C $(PRINTF_DIR)

leaks:
				@valgrind --leak-check=full --show-leak-kinds=all --suppressions=$(SUPPRESSION)  ./$(NAME)

re :			fclean all
