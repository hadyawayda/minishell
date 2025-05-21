/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:13:59 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/07 19:58:11 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer.h"

typedef enum e_node_type
{
	N_CMD,  /* leaf: argv[] + redirs[] */
	N_PIPE, /* binary: left | right    */
	N_AND,  /* binary: left && right   */
	N_OR    /* binary: left || right   */
}					t_node_type;

typedef struct s_redir
{
	t_tokentype op; /* T_REDIR_IN / OUT / APPEND / HERE */
	char *target;   /* filename or heredoc body         */
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd_leaf
{
	char **argv; /* NULL‑terminated                  */
	t_redir			*redirs;
}					t_cmd_leaf;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	t_cmd_leaf cmd; /* only valid when type == N_CMD    */
}					t_ast;

int					check_operator_sequence(t_token tokens[]);
int					check_dollar_paren(t_token tokens[]);

void				traverse_ast(t_ast *n);
void				visualize_tree(t_ast *root);
void				free_tokens(t_token *tokens);
void				visualize_heredoc_tokens(t_token tokens[]);
void				free_ast(t_ast *node);
void				print_tokens(t_token *tokens);

t_ast				*parse_expr(void);
t_ast				*parse_pipe(void);
t_ast				*parse_factor(void);
t_ast				*parse_command(void);
t_ast				*build_ast(t_token *tokens);
