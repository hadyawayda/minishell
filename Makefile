NAME =			michel
CC =			gcc
AR =			ar rcs
CFLAGS =		-g -O0
LIBFT_DIR =		includes/libft
LIBFT =			$(LIBFT_DIR)/libft.a
PRINTF_DIR =	includes/ft_printf
PRINTF =		$(PRINTF_DIR)/libftprintf.a
SUPPRESSION =	includes/utils/ignore_readline.supp

# Source directory prefixes
SRC_DIR					:= src
PROGRAM_DIR			:= $(SRC_DIR)/core/program
ENV_DIR					:= $(SRC_DIR)/core/env
SIGNALS_DIR			:= $(SRC_DIR)/core/signals
PARSER_DIR			:= $(SRC_DIR)/lexer/parser
TOKENIZER_DIR		:= $(SRC_DIR)/lexer/tokenizer

# Top-level sources
SRC            := $(SRC_DIR)/main.c

PROGRAM_SRCS		:= loop.c cleaner.c initializer.c program.c

# Per-component source filenames (relative to their directory)
ENV_SRCS				:= expansion/expansion.c getters/list_env.c getters/list_export.c getters/merge_sort.c \
									initialization/cleaner.c initialization/cloners.c initialization/helpers.c initialization/initializer.c \
									setters/helpers.c setters/setter.c setters/unset.c

SIGNALS_SRCS		:= signals.c

PARSER_SRCS			:= ast_builder.c ast_traverser.c heredoc.c parser_utils.c parser.c syntax_checker.c syntax_checker_helpers.c tree_visualizer.c

TOKENIZER_SRCS	:= dollar_parser.c expansion.c tokenization.c helpers.c operator_parser.c quote_parser.c word_parser.c

# Prefix them with their directories
PROGRAM					:= $(addprefix $(PROGRAM_DIR)/,$(PROGRAM_SRCS))
ENV							:= $(addprefix $(ENV_DIR)/,$(ENV_SRCS))
SIGNALS					:= $(addprefix $(SIGNALS_DIR)/,$(SIGNALS_SRCS))
PARSER					:= $(addprefix $(PARSER_DIR)/,$(PARSER_SRCS))
TOKENIZER				:= $(addprefix $(TOKENIZER_DIR)/,$(TOKENIZER_SRCS))

# Build output directory
OBJDIR					:= includes/objs

# All sources and objects
SRCS						:= $(SRC) $(ENV) $(PROGRAM) $(SIGNALS) $(TOKENIZER) $(PARSER)
OBJS						:= $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

all	:			$(NAME)

$(NAME) :		$(OBJS) $(LIBFT) $(PRINTF)
				@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $@ -lreadline -lm

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
