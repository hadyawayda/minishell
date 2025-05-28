/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:13:59 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/28 23:17:39 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer.h"

#define END_TOKEN ((t_tokentype)-1)

typedef enum e_node_type
{
	N_CMD,  /* leaf: argv[] + redirs[] */
	N_PIPE, /* binary: left | right    */
	N_AND,  /* binary: left && right   */
	N_OR    /* binary: left || right   */
}						t_node_type;

typedef struct s_redir
{
	t_tokentype op; /* T_REDIR_IN / OUT / APPEND / HERE */
	char *target;   /* filename or heredoc body         */
	struct s_redir		*next;
}						t_redir;

typedef struct s_argnode
{
	char *value;     /* the token text, e.g. "foo" or "*.c" */
	bool expandable; /* true ⇒ later wildcard pass may expand */
	struct s_argnode	*next;
}						t_argnode;

typedef struct s_cmd_leaf
{
	char *command;   /* e.g. "echo"                             */
	char **options;  /* NULL-terminated array of options "-l"  */
	t_argnode *args; /* head of list of arguments + flags */
	t_redir *redirs; /* as before                              */
}						t_cmd_leaf;

typedef struct s_ast
{
	t_node_type			type;
	struct s_ast		*left;
	struct s_ast		*right;
	t_cmd_leaf cmd; /* only valid when type == N_CMD    */
}						t_ast;
typedef struct s_parser
{
	t_token *tokens; /* the token array */
	int pos;         /* current index  */
}						t_parser;

char					*expand_line_heredoc(t_shell *shell, const char *line);
char					*make_chunk(t_shell *shell, const char *line,
							int expand, size_t *chunk_len);
char					*append_buf(char *buf, size_t len, const char *chunk,
							size_t chunk_len);

int						check_operator_sequence(t_token tokens[]);
int						check_dollar_paren(t_token tokens[]);
int						is_redir(t_tokentype t);
int						check_leading_token(t_token tokens[]);

void					traverse_ast(t_ast *n);
void					visualize_tree(t_ast *root);
void					free_tokens(t_token *tokens);
void					visualize_heredoc_tokens(t_token tokens[]);
void					free_ast(t_ast *node);
void					print_tokens(t_token *tokens);
void					tree_parser(t_ast *root);
void					count_opts(t_parser *p, int *n_opts);
void					fill_cmd_node(t_parser *p, t_ast *node);
void					handle_word_token(t_ast *node, t_token *tok,
							t_argnode **args_head, t_argnode **args_tail);

t_ast					*parse_expr(t_parser *p);
t_ast					*parse_pipe(t_parser *p);
t_ast					*parse_factor(t_parser *p);
t_ast					*parse_command(t_parser *p);
t_ast					*build_ast(t_token *tokens);
t_ast					*alloc_cmd_node(int n_opts);

t_token					*peek(t_parser *p);
t_token					*next(t_parser *p);
