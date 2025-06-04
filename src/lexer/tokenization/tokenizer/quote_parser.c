/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:24:18 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/27 20:33:46 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/lexer.h"

int	contains_unclosed_quote(const char *in, size_t pos, char q)
{
	while (in[pos])
	{
		if (in[pos] == q)
			return (0);
		pos++;
	}
	printf("Unclosed quote detected\n");
	return (1);
}

int	process_quoted_content(t_shell *sh, const char *in, t_tokenstate *st,
		char q)
{
	while (in[st->i] && in[st->i] != q)
	{
		if (st->skip_expansion && in[st->i] == '$')
		{
			append_char_inplace(&st->cur, in[st->i], &st->i);
			word_parser(in, st);
			continue ;
		}
		if (q == '"' && in[st->i] == '$')
			handle_expansion(sh, in, &st->i, &st->cur);
		else if (in[st->i] == '*')
		{
			append_char_inplace(&st->cur, WILD_UNEXPANDABLE, &st->i);
			append_char_inplace(&st->cur, '*', &st->i);
		}
		else
			append_char_inplace(&st->cur, in[st->i], &st->i);
	}
	return (0);
}

/*
**   1) check for closing quote
**   2) skip the opening quote
**   3) delegate to process_quoted_content
**   4) skip the closing quote
*/
int	quote_parser(t_shell *sh, const char *in, t_tokenstate *st)
{
	char	q;

	q = in[st->i];
	if (contains_unclosed_quote(in, st->i + 1, q) == 1)
		return (-1);
	st->i++;
	process_quoted_content(sh, in, st, q);
	if (in[st->i] == q)
		st->i++;
	return (0);
}
