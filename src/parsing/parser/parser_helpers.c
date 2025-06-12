/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:22:15 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/12 23:33:26 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*peek(t_parser *p)
{
	return (&p->tokens[p->pos]);
}

t_token	*next(t_parser *p)
{
	return (&p->tokens[p->pos++]);
}

void	free_tokens(t_token *tokens)
{
	int		i;

	i = 0;
	while (tokens[i].type != (t_tokentype)-1)
	{
		free(tokens[i].value);
		free(tokens[i].heredoc);
		i++;
	}
	free(tokens);
}
