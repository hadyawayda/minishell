/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 04:49:44 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/04 03:56:33 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

char	**token_builder(t_shell *shell, const char *input)
{
	char	**tokens;
	char	*cur;
	bool	had_quotes;

	int i, j;
	i = j = 0;
	had_quotes = false;
	tokens = malloc(sizeof(char *) * MAX_TOKENS);
	if (!tokens)
		return (NULL);
	cur = ft_strdup("");
	if (!cur)
	{
		free(tokens);
		return (NULL);
	}
	while (input[i] && j < MAX_TOKENS - 1)
	{
		while (input[i] && ft_isspace((unsigned char)input[i]))
		{
			if (cur[0] != '\0' || had_quotes)
			{
				tokens[j++] = ft_strdup(cur);
				had_quotes = false;
				free(cur);
				cur = ft_strdup("");
			}
			i++;
		}
		if (!input[i])
			break ;
		if (input[i] == '$')
		{
			if (dollar_parser(shell, input, &i, &cur, &had_quotes) == -1)
				return (free_tokens(tokens, j), free(cur), NULL);
			continue ;
		}
		if (input[i] == '\'' || input[i] == '"')
		{
			had_quotes = true;
			if (quote_parser(shell, input, &i, &cur) == -1)
				return (free_tokens(tokens, j), free(cur), NULL);
			continue ;
		}
		if (is_operator_char(input[i]))
		{
			if (cur[0] != '\0' || had_quotes)
			{
				tokens[j++] = ft_strdup(cur);
				had_quotes = false;
				free(cur);
				cur = ft_strdup("");
			}
			operator_parser(input, &i, tokens, &j);
			continue ;
		}
		if (!ft_isdelimiter(input[i]))
			word_parser(input, &i, &cur);
		if (ft_isdelimiter(input[i]) || is_operator_char(input[i])
			|| input[i] == '\0')
		{
			if (cur[0] != '\0' || had_quotes)
				tokens[j++] = ft_strdup(cur);
			had_quotes = false;
			free(cur);
			cur = ft_strdup("");
		}
	}
	if ((cur[0] != '\0' || had_quotes) && j < MAX_TOKENS - 1)
		tokens[j++] = ft_strdup(cur);
	free(cur);
	tokens[j] = NULL;
	return (tokens);
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

void	tokenizer(t_shell *shell, char *input)
{
	char	**tokens;
	int		i;
	char	*expanded_input;

	tokens = token_builder(shell, input);
	if (tokens)
	{
		print_tokens(tokens);
		i = 0;
		while (tokens[i])
			free(tokens[i++]);
		free(tokens);
	}
}
