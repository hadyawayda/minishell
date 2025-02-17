/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 04:48:14 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/16 22:16:49 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../core/core.h"

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

void				parser(t_shell *shell, char *input);
void				free_string_array(char **array);
void				tokenizer(char *input);

#endif