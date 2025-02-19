/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:56:06 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/19 03:49:00 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	word_parser(const char *input, char **tokens, int *i, int *j, int merge)
{
	int		start;
	char	*new_token;
	char	*temp;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|'
		&& input[*i] != '&' && input[*i] != '<' && input[*i] != '>'
		&& input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	new_token = ft_substring(input, start, *i);
	if (new_token && merge && *j > 0 && !ft_isspace(input[*i
			- ft_strlen(new_token)]))
	{
		temp = ft_strjoin(tokens[*j - 1], new_token);
		free(tokens[*j - 1]);
		free(new_token);
		tokens[*j - 1] = temp;
	}
	else if (new_token)
		tokens[(*j)++] = new_token;
}
