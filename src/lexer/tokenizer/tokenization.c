/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 04:49:44 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/16 05:10:10 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

#define MAX_TOKENS 4096
#define MAX_TOKEN_SIZE 1024

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

void	parse_word(const char *input, char **tokens, int *i, int *j)
{
	int	start;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|'
		&& input[*i] != '&' && input[*i] != '<' && input[*i] != '>'
		&& input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	tokens[(*j)++] = substr(input, start, *i);
}

char	**tokenize(const char *input)
{
	char	**tokens;
	int		i;
	int		j;
	int		merge;

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
			parse_word(input, tokens, &i, &j);
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

int	main(void)
{
	char	**tokens;
	int		i;

	char input[] = "/bin/ec'ho' 'a'    'asd' | grep Hello \
		&& cat<input.txt >> output.txt ";
	tokens = tokenize(input);
	if (tokens)
	{
		print_tokens(tokens);
		i = 0;
		while (tokens[i])
			free(tokens[i++]);
		free(tokens);
	}
	return (0);
}

// token_t	*tokenize(char *input)
// {
// 	token_t	*head;
// 	token_t	*current;
// 	int		i;
// 	int		start;

// 	head = NULL;
// 	current = NULL;
// 	i = 0;
// 	start = 0;
// 	while (input[i])
// 	{
// 		while (input[i] == ' ' || input[i] == '\t')
// 			i++;
// 		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
// 		{
// 			start = i;
// 			if (input[i] == '>' && input[i + 1] == '>')
// 				i++;
// 			if (input[i] == '<' && input[i + 1] == '<')
// 				i++;
// 			add_token(&head, ft_strndup(input + start, i - start + 1),
// 				TOKEN_OPERATOR);
// 			i++;
// 			continue ;
// 		}
// 		start = i;
// 		while (input[i] && input[i] != ' ' && input[i] != '|' && input[i] != '>'
// 			&& input[i] != '<')
// 			i++;
// 		if (i > start)
// 		{
// 			add_token(&head, ft_strndup(input + start, i - start),
// TOKEN_ARGUMENT);
// 		}
// 	}
// 	return (head);
// }
