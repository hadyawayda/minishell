/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:54:28 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/19 02:58:11 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	operator_parser(const char *input, char **tokens, int *i, int *j)
{
	int	op_len;

	op_len = 1;
	if ((input[*i] == '|' && input[*i + 1] == '|') || (input[*i] == '&'
			&& input[*i + 1] == '&') || (input[*i] == '>' && input[*i
			+ 1] == '>') || (input[*i] == '<' && input[*i + 1] == '<'))
		op_len = 2;
	tokens[(*j)++] = ft_substring(input, *i, *i + op_len);
	*i += op_len;
}
