/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 04:49:44 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/14 04:59:13 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// you light up my world
token_t	*tokenize(char *input)
{
	token_t	*head;
	token_t	*current;
	int		i;
	int		start;

	head = NULL;
	current = NULL;
	i = 0;
	start = 0;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			start = i;
			if (input[i] == '>' && input[i + 1] == '>')
				i++;
			if (input[i] == '<' && input[i + 1] == '<')
				i++;
			add_token(&head, strndup(input + start, i - start + 1),
				TOKEN_OPERATOR);
			i++;
			continue ;
		}
		start = i;
		while (input[i] && input[i] != ' ' && input[i] != '|' && input[i] != '>'
			&& input[i] != '<')
			i++;
		if (i > start)
		{
			add_token(&head, strndup(input + start, i - start), TOKEN_ARGUMENT);
		}
	}
	return (head);
}
