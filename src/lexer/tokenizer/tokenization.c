/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 04:49:44 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/21 04:39:06 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

int	is_operator_char(char c)
{
	if (c == '|' || c == '&' || c == '<' || c == '>')
		return (1);
	return (0);
}

char	**tokenize(const char *input)
{
	char	**tokens;
	int		i;
	int		j;
	int		merge;
	int		w;

	i = 0;
	j = 0;
	merge = 0;
	tokens = malloc(sizeof(char *) * MAX_TOKENS);
	if (!tokens)
		return (NULL);
	while (input[i] != '\0' && j < MAX_TOKENS - 1)
	{
		skip_whitespace(input, &i);
		if (!input[i])
			break ;
		if (input[i] == '\'' || input[i] == '"')
		{
			if (quote_parser(input, tokens, &i, &j, &merge) == -1)
			{
				while (j > 0)
					free(tokens[--j]);
				free(tokens);
				return (NULL);
			}
		}
		else if (is_operator_char(input[i]))
			operator_parser(input, tokens, &i, &j);
		else
			word_parser(input, tokens, &i, &j, &merge);
	}
	tokens[j] = NULL;
	return (tokens);
}

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
}

void	tokenizer(char *input)
{
	char	**tokens;
	int		i;
	char	*expanded_input;

	tokens = tokenize(input);
	if (tokens)
	{
		print_tokens(tokens);
		i = 0;
		while (tokens[i])
			free(tokens[i++]);
		free(tokens);
	}
}
