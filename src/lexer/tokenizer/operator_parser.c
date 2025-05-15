/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:54:28 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/15 20:55:48 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

bool	is_double_operator(const char *in, int idx)
{
	return ((in[idx] == '|' && in[idx + 1] == '|') || (in[idx] == '&' && in[idx
			+ 1] == '&') || (in[idx] == '<' && in[idx + 1] == '<')
		|| (in[idx] == '>' && in[idx + 1] == '>'));
}

t_tokentype	get_double_operator_type(const char *op)
{
	if (op[0] == '|' && op[1] == '|')
		return (T_OR);
	if (op[0] == '&' && op[1] == '&')
		return (T_AND);
	if (op[0] == '<' && op[1] == '<')
		return (T_REDIR_HERE);
	if (op[0] == '>' && op[1] == '>')
		return (T_REDIR_APPEND);
	return (T_WORD);
}

t_tokentype	get_single_operator_type(char c)
{
	if (c == '|')
		return (T_PIPE);
	else if (c == '<')
		return (T_REDIR_IN);
	else if (c == '>')
		return (T_REDIR_OUT);
	else if (c == '(')
		return (T_LPAREN);
	else if (c == ')')
		return (T_RPAREN);
	else
		return (T_WORD);
}

void	operator_parser(const char *in, t_token tokens[], t_tokenstate *st)
{
	char		*op;
	t_tokentype	type;
	size_t		len;

	if (is_double_operator(in, st->i))
	{
		type = get_double_operator_type(in + st->i);
		len = 2;
	}
	else
	{
		type = get_single_operator_type(in[st->i]);
		len = 1;
	}
	op = ft_strndup(in + st->i, len);
	tokens[st->j].type = type;
	tokens[st->j].value = op;
	tokens[st->j].is_quoted = false;
	st->j++;
	st->i += len;
}
