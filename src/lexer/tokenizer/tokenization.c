/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 04:49:44 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/18 19:25:44 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

char	**tokenize(const char *input)
{
	char	**tokens;
	int		i;
	int		j;
	int		merge;
	char	*expanded;

	tokens = malloc(sizeof(char *) * MAX_TOKENS);
	if (!tokens)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i] && j < MAX_TOKENS - 1)
	{
		skip_whitespace(input, &i);
		if (!input[i])
			break ;
		merge = (j > 0 && i > 0 && !ft_isspace(input[i - 1]));
		if (input[i] == '\'' || input[i] == '"')
		{
			if (parse_quote(input, tokens, &i, &j, merge) == -1)
				return (free(tokens), NULL);
		}
		else if (input[i] == '|' || input[i] == '&' || input[i] == '<'
			|| input[i] == '>')
			parse_operator(input, tokens, &i, &j);
		else
			parse_word(input, tokens, &i, &j, merge);
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
		printf("Token %d: [%s]\n", i, tokens[i]);
		i++;
	}
}

void	tokenizer(char *input)
{
	char	**tokens;
	int		i;
	char	*expanded_input;

	expanded_input = expand_variable(input);
	tokens = tokenize(expanded_input);
	free(expanded_input);
	if (tokens)
	{
		print_tokens(tokens);
		i = 0;
		while (tokens[i])
			free(tokens[i++]);
		free(tokens);
	}
}
