/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:13:59 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/05 00:40:38 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer.h"

typedef enum e_redir_kind {
  R_IN,
  R_OUT,
  R_APPEND,
  R_HERE
} t_redir_kind;

typedef struct s_redir {
  t_redir_kind    kind;
  char           *target;
  struct s_redir *next;
} t_redir;

typedef struct s_command {
  char          **argv;
  t_redir        *redirs;
  bool            background;
  struct s_command *next;
} t_command;

typedef struct s_job {
  t_command *first;
} t_job;

t_job *parse_tokens(t_token tokens[]);