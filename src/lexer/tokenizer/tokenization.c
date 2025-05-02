/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 04:49:44 by hawayda           #+#    #+#             */
/*   Updated: 2025/03/03 19:15:24 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

char **token_builder(const char *input)
{
    char  **tokens;
    char   *current_token;
    int     i = 0, j = 0;
    bool    token_had_quotes = false;      /* survives until we push */

    tokens = malloc(sizeof(char *) * MAX_TOKENS);
    if (!tokens)
        return NULL;
    current_token = ft_strdup("");
    if (!current_token)
        return free(tokens), NULL;
    while (input[i] && j < MAX_TOKENS - 1)
    {
        skip_whitespace(input, &i);
        if (!input[i])
            break;
        if (input[i] == '\'' || input[i] == '"')
        {
            token_had_quotes = true;               /* remember */
            if (quote_parser(input, &i, &current_token) == -1)
                return free_tokens(tokens, j), free(current_token), NULL;
        }
        else if (is_operator_char(input[i]))
            operator_parser(input, &i, tokens, &j);
        else if (!ft_isdelimiter(input[i]))
            word_parser(input, &i, &current_token);
        if (ft_isdelimiter(input[i]) || is_operator_char(input[i]) || !input[i])
        {
            if (current_token[0] != '\0' || token_had_quotes)
                tokens[j++] = ft_strdup(current_token);
            token_had_quotes = false;
            free(current_token);
            current_token = ft_strdup("");
        }
    }
    if ((current_token[0] != '\0' || token_had_quotes) && j < MAX_TOKENS - 1)
        tokens[j++] = ft_strdup(current_token);
    free(current_token);
    tokens[j] = NULL;
    return tokens;
}

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("%s", tokens[i]);
		if (tokens[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}

void	tokenizer(char *input)
{
	char	**tokens;
	int		i;
	char	*expanded_input;

	tokens = token_builder(input);
	if (tokens)
	{
		print_tokens(tokens);
		i = 0;
		while (tokens[i])
			free(tokens[i++]);
		free(tokens);
	}
}
