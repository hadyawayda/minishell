/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:24:18 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/22 19:59:00 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

int	contains_unclosed_quote(const char *in, size_t pos, char q)
{
	while (in[pos])
	{
		if (in[pos] == q)
			return (0);
		pos++;
	}
	ft_printf("Unclosed quote detected\n");
	return (1);
}

int	quote_parser(t_shell *sh, const char *in, t_tokenstate *st)
{
	char	q;

	q = in[st->i];
	if (contains_unclosed_quote(in, st->i + 1, q) == 1)
		return (-1);
	st->i++;
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
		else
			append_char_inplace(&st->cur, in[st->i], &st->i);
	}
	if (in[st->i] == q)
		st->i++;
	return (0);
}
