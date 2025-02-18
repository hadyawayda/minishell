/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 04:48:14 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/18 19:25:58 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define MAX_TOKENS 4096

# include "../core/core.h"

typedef enum e_quote
{
	NONE,
	SINGLE,
	DOUBLE
}					t_quote;

typedef enum
{
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_OPERATOR,
	TOKEN_REDIRECTION
}					token_type_t;

typedef struct s_token
{
	token_type_t	type;
	char			*value;
	struct s_token	*next;
}					token_t;

int					parse_quote(const char *input, char **tokens, int *i,
						int *j, int merge);

char				*expand_variable(const char *input);

void				parser(t_shell *shell, char *input);
void				free_string_array(char **array);
void				tokenizer(char *input);
void				parse_operator(const char *input, char **tokens, int *i,
						int *j);
void				parse_word(const char *input, char **tokens, int *i, int *j,
						int merge);
void				skip_whitespace(const char *input, int *i);

#endif