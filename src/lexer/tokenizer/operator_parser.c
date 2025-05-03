/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:54:28 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/04 01:32:48 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

/* operator_parser.c ------------------------------------------------------ */
void	operator_parser(const char *in, int *i, char **tokens, int *j)
{
	char	*op;

	/* –– first grab the four two-character operators –– */
	if ((in[*i] == '|' && in[*i + 1] == '|')     /*  ||  */
		|| (in[*i] == '&' && in[*i + 1] == '&')  /*  &&  */
		|| (in[*i] == '<' && in[*i + 1] == '<')  /*  <<  */
		|| (in[*i] == '>' && in[*i + 1] == '>')) /*  >>  */
	{
		op = ft_strndup(in + *i, 2);
		*i += 2;
	}
	else
	{ /* single-char | & < > ( ) */
		op = ft_strndup(in + *i, 1);
		(*i)++;
	}
	tokens[(*j)++] = op;
}
