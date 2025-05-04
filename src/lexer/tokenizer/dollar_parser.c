/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:24:18 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/04 03:30:51 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	literal_dollars(const char *in, int *i, char **cur)
{
	while (in[*i] == '$' && in[*i + 1] == '$')
	{
		append_char_inplace(cur, '$', i);
		append_char_inplace(cur, '$', i);
	}
}

int	dollar_parser(t_shell *sh, const char *in, int *i, char **cur,
		bool *had_quotes)
{
	char *nbr, *tmp;
	if (in[*i] != '$')
		return (0);
	if (in[*i + 1] == '$')
	{
		literal_dollars(in, i, cur);
		return (0);
	}
	if (in[*i + 1] == '"' || in[*i + 1] == '\'')
	{
		*had_quotes = true;
		(*i)++;
		return (quote_parser(sh, in, i, cur));
	}
	handle_expansion(sh, in, i, cur);
	return (0);
}
