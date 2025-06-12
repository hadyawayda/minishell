# ──────────────────────────────────────────────────────────────────────────────
# PROJECT DIRECTORIES
# ──────────────────────────────────────────────────────────────────────────────

SRC_DIR					:= src
LIB_DIR					:= lib
LIBFT_DIR				:= $(LIB_DIR)/libft

# ──────────────────────────────────────────────────────────────────────────────
# PROJECT SETTINGS
# ──────────────────────────────────────────────────────────────────────────────

NAME					:= minishell
CC						:= gcc
AR						:= ar rcs
CFLAGS					:= -g -O0 -I $(LIB_DIR)
OBJDIR					:= objs

# ──────────────────────────────────────────────────────────────────────────────
# LIBRARIES (libft, readline)
# ──────────────────────────────────────────────────────────────────────────────

LIBFT					:= $(LIBFT_DIR)/libft.a
SUPPRESSION				:= $(LIB_DIR)/utils/ignore_readline.supp

# ──────────────────────────────────────────────────────────────────────────────
# DIRECTORY LAYOUT
# ──────────────────────────────────────────────────────────────────────────────

# Core directories
CORE_DIR				:= $(SRC_DIR)/core
ENV_DIR					:= $(CORE_DIR)/env
PROGRAM_DIR				:= $(CORE_DIR)/program
SIGNALS_DIR				:= $(CORE_DIR)/signals

# ENV directories:
EXPANSION_DIR			:= $(ENV_DIR)/expansion
GETTERS_DIR				:= $(ENV_DIR)/getters
INITIALIZATION_DIR		:= $(ENV_DIR)/initialization
SETTERS_DIR				:= $(ENV_DIR)/setters

# Lexer directories
TOKENIZATION_DIR		:= $(SRC_DIR)/tokenization
PARSING_DIR				:= $(SRC_DIR)/parsing

# Parsing directories:
HEREDOC_DIR				:= $(PARSING_DIR)/heredoc
PARSER_SUBDIR			:= $(PARSING_DIR)/parser
SYNTAX_CHECKER_DIR		:= $(PARSING_DIR)/syntax_checker
TREE_DIR				:= $(PARSING_DIR)/tree

# Tokenization directories:
TOKENIZER_DIR			:= $(TOKENIZATION_DIR)/tokenizer
WILDCARD_DIR			:= $(TOKENIZATION_DIR)/wildcard

# Execution directories
EXECUTION_DIR			:= $(SRC_DIR)/execution
BUILTINS_DIR			:= $(EXECUTION_DIR)/builtins

# ──────────────────────────────────────────────────────────────────────────────
# SOURCE FILES (relative to the project root)
# ──────────────────────────────────────────────────────────────────────────────

# 1) Top‐level source
MAIN					:= $(SRC_DIR)/main.c

# 2) PROGRAM sources (just filenames; will be prefixed later)
PROGRAM_SRCS			:= loop.c cleaner.c initializer.c program.c

# 3) ENV sub‐components: list only the .c filenames here
EXPANSION_SRCS			:= expansion_helpers.c expansion.c
GETTERS_SRCS			:= list_export.c merge_sort.c
INITIALIZATION_SRCS		:= cleaner.c cloners.c helpers.c
SETTERS_SRCS			:= helpers.c setter.c unset.c

# 4) SIGNALS sources
SIGNALS_SRCS			:= signals.c

# 5) PARSING sources
PARSER_TOP_SRCS			:= parser.c
HEREDOC_SRCS			:= heredoc.c heredoc_helpers.c
PARSER_SRCS				:= parser_helpers.c
SYNTAX_CHECKER_SRCS		:= syntax_checker.c syntax_checker_helpers.c
TREE_SRCS				:= ast_builder.c parse_command_helpers.c parse_command.c tree_cleaner.c

# 6) TOKENIZATION sources
TOKENIZATION_TOP_SRCS	:= tokenization.c
TOKENIZER_SRCS			:= dollar_parser.c helpers.c operator_parser.c quote_parser.c word_parser.c
WILDCARD_SRCS			:= wildcard_expansion.c wildcard_matcher_helpers.c wildcard_matcher.c

# 7) EXECUTION sources
EXECUTION_SRCS			:= build_argv.c build_envp.c execute_operators.c execution_dispatcher.c execution_helpers.c redirection_helpers.c
BUILTINS_SRCS			:= environment_builtins.c cd.c cd_helpers.c echo_builtin.c exit_builtin.c

# ──────────────────────────────────────────────────────────────────────────────
# PREFIX each group of filenames with its directory
# ──────────────────────────────────────────────────────────────────────────────

# PROGRAM
PROGRAM					:= $(addprefix $(PROGRAM_DIR)/,$(PROGRAM_SRCS))

# ENV: break into sub‐directories, then combine
EXPANSION				:= $(addprefix $(EXPANSION_DIR)/,$(EXPANSION_SRCS))
GETTERS					:= $(addprefix $(GETTERS_DIR)/,$(GETTERS_SRCS))
INITIALIZATION			:= $(addprefix $(INITIALIZATION_DIR)/,$(INITIALIZATION_SRCS))
SETTERS					:= $(addprefix $(SETTERS_DIR)/,$(SETTERS_SRCS))
ENV						:= $(EXPANSION) $(GETTERS) $(INITIALIZATION) $(SETTERS)

# SIGNALS
SIGNALS					:= $(addprefix $(SIGNALS_DIR)/,$(SIGNALS_SRCS))

# PARSING: one top‐level parser.c, plus subdirectories
PARSER_TOP				:= $(addprefix $(PARSING_DIR)/,$(PARSER_TOP_SRCS))
PARSER_MIDDLE			:= $(addprefix $(PARSER_SUBDIR)/,$(PARSER_SRCS))
TREE					:= $(addprefix $(TREE_DIR)/,$(TREE_SRCS))
SYNTAX_CHECKER			:= $(addprefix $(SYNTAX_CHECKER_DIR)/,$(SYNTAX_CHECKER_SRCS))
HEREDOC					:= $(addprefix $(HEREDOC_DIR)/,$(HEREDOC_SRCS))
PARSING					:= $(PARSER_TOP) $(PARSER_MIDDLE) $(TREE) $(SYNTAX_CHECKER) $(HEREDOC)

# TOKENIZATION: one top‐level tokenization.c, plus subdirectories
TOKENIZATION_TOP		:= $(addprefix $(TOKENIZATION_DIR)/,$(TOKENIZATION_TOP_SRCS))
TOKENIZER				:= $(addprefix $(TOKENIZER_DIR)/,$(TOKENIZER_SRCS))
WILDCARD				:= $(addprefix $(WILDCARD_DIR)/,$(WILDCARD_SRCS))
TOKENIZATION			:= $(TOKENIZATION_TOP) $(TOKENIZER) $(WILDCARD)

# EXECUTION
EXECUTION_TOP			:= $(addprefix $(EXECUTION_DIR)/,$(EXECUTION_SRCS))
BUILTINS				:= $(addprefix $(BUILTINS_DIR)/,$(BUILTINS_SRCS))
EXECUTION				:= $(EXECUTION_TOP) $(BUILTINS)

# ──────────────────────────────────────────────────────────────────────────────
# ALL SOURCE FILES COMBINED
# ──────────────────────────────────────────────────────────────────────────────

SRCS					:= $(MAIN) $(PROGRAM) $(ENV) $(SIGNALS) $(TOKENIZATION) $(PARSING) $(EXECUTION)

# ──────────────────────────────────────────────────────────────────────────────
# OBJECT FILES: simply replace “.c” with “$(OBJDIR)/…/*.o”
# ──────────────────────────────────────────────────────────────────────────────

OBJS					:= $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

# ──────────────────────────────────────────────────────────────────────────────
# DEFAULT TARGET
# ──────────────────────────────────────────────────────────────────────────────

all:					$(NAME)

# ──────────────────────────────────────────────────────────────────────────────
# LINKING: build the final executable
# ──────────────────────────────────────────────────────────────────────────────

$(NAME):				$(OBJS) $(LIBFT)
						@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@ -lreadline -lm

# ──────────────────────────────────────────────────────────────────────────────
# BUILD libft if they don’t exist
# ──────────────────────────────────────────────────────────────────────────────

$(LIBFT):
						@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

# ──────────────────────────────────────────────────────────────────────────────
# PATTERN RULE TO COMPILE ANY .c → .o under $(OBJDIR)
# ──────────────────────────────────────────────────────────────────────────────

$(OBJDIR)/%.o:			%.c
						@mkdir -p $(dir $@)
						@$(CC) $(CFLAGS) -c $< -o $@

# ──────────────────────────────────────────────────────────────────────────────
# CLEAN & FCLEAN
# ──────────────────────────────────────────────────────────────────────────────

clean:					
						@rm -f $(OBJS)
						@rm -rf $(OBJDIR)
						@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean:					clean
						@rm -f $(NAME)
						@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re:						fclean all

# ──────────────────────────────────────────────────────────────────────────────
# OPTIONAL VALGRIND TARGET
# ──────────────────────────────────────────────────────────────────────────────

leaks:
						@valgrind --leak-check=full --show-leak-kinds=all --suppressions=$(SUPPRESSION) ./$(NAME)

qleaks:
						@valgrind -q --leak-check=full --suppressions=$(SUPPRESSION) ./$(NAME)
