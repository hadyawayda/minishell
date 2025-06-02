/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:09:17 by fel-ghaz          #+#    #+#             */
/*   Updated: 2025/05/30 21:36:05 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE 700

# include "../src/core/core.h"
# include "../src/execution/execution.h"
# include "../src/lexer/lexer.h"
# include "../src/lexer/parser.h"
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	t_env			*env;
	int				exit_requested;
	int				last_exit_status;
}					t_shell;

typedef enum e_tokentype
{
	T_WORD,
	T_PIPE,
	T_AND,
	T_OR,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_HERE,
	T_REDIR_APPEND,
	T_LPAREN,
	T_RPAREN,
}				t_tokentype;

typedef struct s_token
{
	t_tokentype	type;
	bool		is_quoted;
	char		*value;
	char		*heredoc;
}				t_token;

typedef struct s_tokenstate
{
	int			i;
	int			j;
	bool		had_quotes;
	bool		skip_expansion;
	char		*cur;
}				t_tokenstate;

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

#endif
