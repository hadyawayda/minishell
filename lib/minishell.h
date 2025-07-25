/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:09:17 by fel-ghaz          #+#    #+#             */
/*   Updated: 2025/06/18 01:54:52 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ARG_MAX
# define WILD_UNEXPANDABLE '\x1F'
# define _DEFAULT_SOURCE

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
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern sig_atomic_t		g_last_signal;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_shell
{
	t_env				*env;
	int					exit_requested;
	int					last_exit_status;
}						t_shell;

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
}						t_tokentype;

typedef struct s_token
{
	t_tokentype			type;
	bool				is_quoted;
	char				*value;
	char				*heredoc;
}						t_token;

typedef struct s_tokenstate
{
	int					i;
	int					j;
	bool				had_quotes;
	bool				skip_expansion;
	char				*cur;
}						t_tokenstate;

typedef enum e_node_type
{
	N_CMD,
	N_PIPE,
	N_AND,
	N_OR
}						t_node_type;

typedef struct s_redir
{
	t_tokentype			op;
	char				*target;
	struct s_redir		*next;
}						t_redir;

typedef struct s_argnode
{
	char				*value;
	bool				expandable;
	struct s_argnode	*next;
}						t_argnode;

typedef struct s_cmd_leaf
{
	char				*command;
	char				**options;
	t_argnode			*args;
	t_redir				*redirs;
}						t_cmd_leaf;

typedef struct s_ast
{
	t_node_type			type;
	struct s_ast		*left;
	struct s_ast		*right;
	t_cmd_leaf			cmd;
}						t_ast;

typedef struct s_parser
{
	t_token				*tokens;
	int					pos;
}						t_parser;

typedef struct s_cd_ctx
{
	char				*target;
	char				*prev_pwd;
	int					dash;
	int					dbl_sl;
}						t_cd_ctx;

typedef struct s_hd_state
{
	char				*delim;
	int					expand;
	t_shell				*shell;
	char				*buf;
	size_t				len;
}						t_hd_state;

#endif
