/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:56:06 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/22 19:59:02 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	word_parser(const char *in, t_tokenstate *st)
{
	while (in[st->i] && !ft_isdelimiter(in[st->i])
		&& !is_operator_char(in[st->i]) && in[st->i] != '\'' && in[st->i] != '"'
		&& in[st->i] != '$')
	{
		if (in[st->i] == '*')
			st->is_expandable[st->j] = 1;
		append_char_inplace(&st->cur, in[st->i], &st->i);
	}
}
