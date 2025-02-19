/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:56:06 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/20 01:47:37 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	word_parser(const char *input, char **tokens, int *i, int *j, int merge)
{
	int		start;
	char	*new_token;
	char	*temp;
	char	*expanded;

	start = *i;
	while (input[*i] && !ft_isdelimiter(input[*i]) && input[*i] != '\''
		&& input[*i] != '"')
		(*i)++;
	new_token = ft_substring(input, start, *i);
	if (!new_token)
		return ;
	// Handle variable expansion outside of quotes
	if (ft_strchr(new_token, '$'))
	{
		expanded = expand_variable(new_token);
		free(new_token);
		new_token = expanded;
	}
	// Only merge if there's no delimiter between tokens
	if (merge && *j > 0)
	{
		temp = ft_strjoin(tokens[*j - 1], new_token);
		free(tokens[*j - 1]);
		free(new_token);
		tokens[*j - 1] = temp;
	}
	else
		tokens[(*j)++] = new_token;
}
