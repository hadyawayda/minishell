/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 04:48:14 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/04 03:29:48 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define MAX_TOKENS 4096
# define ARG_MAX

# include "../core/core.h"

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
	char		*value;
}				t_token;

int				skip_whitespace(const char *input, int *i);
int				quote_parser(t_shell *sh, const char *in, int *i, char **cur);
int				is_operator_char(char c);
int				dollar_parser(t_shell *sh, const char *in, int *i, char **cur,
					bool *had_quotes);

char			*expand_variable(const char *input);
char			*ft_strjoin_char(char *s1, char c);
char			*append_char(char *s1, char c);

void			parser(t_shell *shell, char *input);
void			free_string_array(char **array);
void			tokenizer(t_shell *shell, char *input);
void			operator_parser(const char *input, int *i, char **tokens,
					int *j);
void			word_parser(const char *input, int *i, char **current_token);
void			free_tokens(char **tokens, int j);
void			handle_expansion(t_shell *sh, const char *in, int *i,
					char **cur);
void			append_char_inplace(char **dst, char c, int *i);

#endif