/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 04:48:14 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/15 20:55:48 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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
	t_tokentype		type;
	char					*value;
	bool					is_quoted;
	char					*heredoc;
}				t_token;

typedef struct s_tokenstate
{
	int			i;
	int			j;
	char		*cur;
	bool		had_quotes;
	bool		skip_expansion;
}				t_tokenstate;

int				quote_parser(t_shell *sh, const char *in, t_tokenstate *st);
int				is_operator_char(char c);
int				dollar_parser(t_shell *sh, const char *in, t_tokenstate *st);
int				check_syntax(t_token tokens[]);

char			*expand_variable(const char *input);
char			*ft_strjoin_char(char *s1, char c);
char			*append_char(char *s1, char c);

void			parser(t_shell *shell, t_token *tokens);
void			free_string_array(char **array);
void			operator_parser(const char *in, t_token tokens[],
					t_tokenstate *st);
void			word_parser(const char *in, t_tokenstate *st);
void			handle_expansion(t_shell *sh, const char *in, int *i,
					char **cur);
void			append_char_inplace(char **dst, char c, int *i);
void			flush_current(t_token tokens[], t_tokenstate *st);
void			append_literal_dollars(const char *in, int *i, char **cur);
void			skip_whitespaces_and_flush(const char *input, t_tokenstate *st,
					t_token tokens[]);
void			collect_heredocs(t_shell *shell, t_token tokens[]);

t_token			*input_tokenizer(t_shell *shell, char *input);

#endif