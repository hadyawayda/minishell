/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:24:18 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/22 19:58:56 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	append_literal_dollars(const char *in, int *i, char **cur)
{
	while (in[*i] == '$' && in[*i + 1] == '$')
	{
		append_char_inplace(cur, '$', i);
		append_char_inplace(cur, '$', i);
	}
}

int	dollar_parser(t_shell *sh, const char *in, t_tokenstate *st)
{
	if (in[st->i + 1] == '"' || in[st->i + 1] == '\'')
	{
		st->had_quotes = true;
		st->i++;
		return (quote_parser(sh, in, st));
	}
	if (st->skip_expansion)
	{
		append_char_inplace(&st->cur, in[st->i], &st->i);
		word_parser(in, st);
		return (0);
	}
	if (in[st->i] != '$')
		return (0);
	if (in[st->i + 1] == '$')
	{
		append_literal_dollars(in, &st->i, &st->cur);
		return (0);
	}
	handle_expansion(sh, in, &st->i, &st->cur);
	return (0);
}
