/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:56:06 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/27 20:05:29 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/lexer.h"

void	word_parser(const char *in, t_tokenstate *st)
{
	while (in[st->i] && !ft_isdelimiter(in[st->i])
		&& !is_operator_char(in[st->i]) && in[st->i] != '\'' && in[st->i] != '"'
		&& in[st->i] != '$')
	{
		append_char_inplace(&st->cur, in[st->i], &st->i);
	}
}
