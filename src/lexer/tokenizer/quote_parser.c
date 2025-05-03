/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:24:18 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/04 01:32:51 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

int	quote_parser(const char *in, int *i, char **cur)
{
	char	quote;
	char	*temp;
	size_t	len;

	quote = in[*i];
	(*i)++;
	if ((quote == '"' || quote == '\'') && in[*i - 2] == '$')
	{
		len = ft_strlen(*cur);
		if (len && (*cur)[len - 1] == '$')
			(*cur)[len - 1] = '\0';
		while (in[*i] && in[*i] != quote)
		{
			if (quote == '"' && in[*i] == '$')
				handle_expansion(in, i, cur);
			else
				append_char_inplace(cur, in[*i], i);
		}
		if (in[*i] == quote)
			(*i)++;
		return (0);
	}
	while (in[*i])
	{
		if (in[*i] == quote)
		{
			(*i)++;
			return (0);
		}
		if (quote == '"' && in[*i] == '$')
			handle_expansion(in, i, cur);
		else
			append_char_inplace(cur, in[*i], i);
	}
	ft_printf("Unclosed quote detected\n");
	return (-1);
}
