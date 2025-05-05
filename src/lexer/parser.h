/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:13:59 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/05 20:21:16 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer.h"

typedef enum e_redir_kind
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HERE
}						t_redir_kind;

typedef struct s_redir
{
	t_redir_kind		kind;
	char				*target;
	struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	char				**argv;
	t_redir				*redirs;
	bool				background;
	struct s_command	*next;
}						t_command;

typedef struct s_job
{
	t_command			*first;
}						t_job;

t_job					*parse_tokens(t_token tokens[]);
t_job					*malloc_job(void);
t_command				*malloc_command(void);
char					**append_argv(char **argv, const char *val);
int						is_redir(t_tokentype type);
t_redir					*malloc_redir(void);
t_redir_kind			map_to_redir_kind(t_tokentype type);
void					execute_job(t_job *job);
void					free_job(t_job *job);
