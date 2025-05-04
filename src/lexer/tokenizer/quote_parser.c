/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:24:18 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/04 04:50:12 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

int	quote_parser(t_shell *sh, const char *in, t_tokenstate *st)
{
	char	q;

	q = in[st->i++];
	while (in[st->i])
	{
		if (in[st->i] == q)
		{
			st->i++;
			return (0);
		}
		if (q == '"' && in[st->i] == '$')
			handle_expansion(sh, in, &st->i, &st->cur);
		else
			append_char_inplace(&st->cur, in[st->i], &st->i);
	}
	ft_printf("Unclosed quote detected\n");
	return (-1);
}
