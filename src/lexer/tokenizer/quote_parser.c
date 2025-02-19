/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:24:18 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/19 03:51:38 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

int	quote_parser(const char *input, char **tokens, int *i, int *j, int *merge)
{
	int		start;
	char	quote;
	char	*new_token;
	char	*temp;
	char	*expanded;

	*merge = (*j > 0 && *i > 0 && !ft_isspace(input[*i - 1]));
	quote = input[*i];
	start = ++(*i);
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i])
	{
		printf("Error: Unterminated quote\n");
		return (-1);
	}
	new_token = ft_substring(input, start, *i);
	(*i)++;
	if (new_token && quote == '"' && ft_strchr(new_token, '$'))
	{
		expanded = expand_variable(new_token);
		free(new_token);
		new_token = expanded;
	}
	if (input[*i] && !ft_isspace(input[*i]) && (input[*i] == '\''
			|| input[*i] == '"'))
		*merge = 1;
	if (new_token && *merge && *j > 0)
	{
		temp = ft_strjoin(tokens[*j - 1], new_token);
		free(tokens[*j - 1]);
		free(new_token);
		tokens[*j - 1] = temp;
	}
	else
		tokens[(*j)++] = new_token;
	return (0);
}
