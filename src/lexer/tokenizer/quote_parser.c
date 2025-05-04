/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:24:18 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/04 03:30:02 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

int	quote_parser(t_shell *sh, const char *in, int *i, char **cur)
{
	char	q;

	q = in[*i];
	(*i)++;
	while (in[*i])
	{
		if (in[*i] == q)
		{
			(*i)++;
			return (0);
		}
		if (q == '"' && in[*i] == '$')
			handle_expansion(sh, in, i, cur);
		else
			append_char_inplace(cur, in[*i], i);
	}
	ft_printf("Unclosed quote detected\n");
	return (-1);
}
