/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:56:06 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/04 03:51:30 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	word_parser(const char *in, int *i, char **cur)
{
	while (in[*i] && !ft_isdelimiter(in[*i]) && !is_operator_char(in[*i])
		&& in[*i] != '\'' && in[*i] != '"' && in[*i] != '$')
		append_char_inplace(cur, in[*i], i);
}
