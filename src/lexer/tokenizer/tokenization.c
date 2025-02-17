/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 04:49:44 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/17 04:58:06 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

#define MAX_TOKENS 4096
#define MAX_TOKEN_SIZE 1024

char	*expand_variable(const char *input);

char	*substr(const char *src, int start, int end)
{
	char	*dest;
	int		len;

	len = end - start;
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	ft_strncpy(dest, src + start, len);
	dest[len] = '\0';
	return (dest);
}

void	skip_whitespace(const char *input, int *i)
{
	while (ft_isspace(input[*i]))
		(*i)++;
}

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
	new_token = substr(input, start, *i);
	(*i)++;
	if (quote == '"' && ft_strchr(new_token, '$'))
	{
		expanded = expand_variable(new_token);
		free(new_token);
		new_token = expanded;
	}
	if (merge && *j > 0 && !ft_isspace(input[*i - (strlen(new_token) + 2)]))
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

void	parse_operator(const char *input, char **tokens, int *i, int *j)
{
	int	op_len;

	op_len = 1;
	if ((input[*i] == '|' && input[*i + 1] == '|') || (input[*i] == '&'
			&& input[*i + 1] == '&') || (input[*i] == '>' && input[*i
			+ 1] == '>') || (input[*i] == '<' && input[*i + 1] == '<'))
		op_len = 2;
	tokens[(*j)++] = substr(input, *i, *i + op_len);
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
	new_token = substr(input, start, *i);
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

char	*expand_variable(const char *input)
{
	int i, start;
	char *result, *var_name, *var_value, *temp;
	result = ft_strdup("");
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			start = i++;
			while (input[i] && input[i] != '\'')
				i++;
			result = ft_strjoin_and_free(result, substr(input, start, i + 1));
			i++;
		}
		else if (input[i] == '$' && input[i + 1] && (ft_isalnum(input[i + 1])
				|| input[i + 1] == '_'))
		{
			start = ++i;
			while (ft_isalnum(input[i]) || input[i] == '_')
				i++;
			var_name = substr(input, start, i);
			var_value = getenv(var_name);
			temp = var_value ? ft_strdup(var_value) : ft_strdup("");
			result = ft_strjoin_and_free(result, temp);
			free(var_name);
		}
		else
		{
			temp = substr(input, i, i + 1);
			result = ft_strjoin_and_free(result, temp);
			i++;
		}
	}
	return (result);
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
