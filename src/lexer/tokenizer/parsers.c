/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:24:18 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/18 19:38:37 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

int	parse_quote(const char *input, char **tokens, int *i, int *j, int merge)
{
	int		start;
	char	quote;
	char	*new_token;
	char	*temp;
	char	*expanded;

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
	if (quote == '"' && ft_strchr(new_token, '$'))
	{
		expanded = expand_variable(new_token);
		new_token = expanded;
	}
	if (input[*i] && (input[*i] == '\'' || input[*i] == '"'))
		merge = 1;
	if (merge && *j > 0)
	{
		temp = ft_strjoin(tokens[*j - 1], new_token);
		free(tokens[*j - 1]);
		tokens[*j - 1] = temp;
	}
	else
		tokens[(*j)++] = new_token;
	return (0);
}

void	parse_operator(const char *input, char **tokens, int *i, int *j)
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

void	parse_word(const char *input, char **tokens, int *i, int *j, int merge)
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
	if (merge && *j > 0 && !ft_isspace(input[*i - ft_strlen(new_token)]))
	{
		temp = ft_strjoin(tokens[*j - 1], new_token);
		free(tokens[*j - 1]);
		free(new_token);
		tokens[*j - 1] = temp;
	}
	else
		tokens[(*j)++] = new_token;
}
