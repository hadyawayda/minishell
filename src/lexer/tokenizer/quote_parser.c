/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:24:18 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/19 05:04:04 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

// Helper function to join string with single char
char	*ft_strjoin_char(char *s1, char c)
{
	char	*result;
	size_t	len;

	len = ft_strlen(s1);
	result = malloc(len + 2); // +1 for new char, +1 for null terminator
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}

char	*expand_variable1(const char *str)
{
	char	*result;
	char	*value;
	char	*var_name;
	int		i;
	int		start;
	char	*temp;

	result = ft_strdup(""); // Initialize with empty string
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && !ft_isspace(str[i + 1]))
		{
			i++;
			start = i;
			// Find the end of the variable name
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			// Extract variable name
			var_name = ft_substring(str, start, i);
			if (!var_name)
			{
				free(result);
				return (NULL);
			}
			// Get value from environment
			value = getenv(var_name);
			free(var_name);
			// Append value or empty string if not found
			if (value)
			{
				temp = ft_strjoin(result, value);
				free(result);
				if (!temp)
					return (NULL);
				result = temp;
			}
			continue ;
		}
		// Append regular character
		temp = ft_strjoin_char(result, str[i]);
		free(result);
		if (!temp)
			return (NULL);
		result = temp;
		i++;
	}
	return (result);
}
// Helper function to check if we're at the start of a variable
static int	is_variable_start(char c, char next_c)
{
	return (c == '$' && next_c && !ft_isspace(next_c));
}

// Helper function to check if character is valid in a variable name
static int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

// Extract and expand variable name
static char	*extract_variable(const char *str, int *pos)
{
	int		i;
	char	*var_name;
	char	*value;

	int start = *pos + 1; // Skip the $
	i = start;
	while (str[i] && is_valid_var_char(str[i]))
		i++;
	var_name = ft_substring(str, start, i);
	if (!var_name)
		return (NULL);
	value = getenv(var_name);
	free(var_name);
	*pos = i - 1; // Update position to end of variable name
	return (value ? ft_strdup(value) : ft_strdup(""));
}

// Append string to builder with proper memory management
static int	append_to_builder(char **builder, const char *str)
{
	char	*temp;

	temp = ft_strjoin(*builder, str);
	free(*builder);
	if (!temp)
		return (-1);
	*builder = temp;
	return (0);
}

// Handle variable expansion within quotes
static int	handle_variable_expansion(t_parser_state *state, const char *input)
{
	char	*expanded;
	int		result;

	if (!is_variable_start(input[state->i], input[state->i + 1]))
		return (0);
	expanded = extract_variable(input, &state->i);
	if (!expanded)
		return (-1);
	result = append_to_builder(&state->builder, expanded);
	free(expanded);
	return (result);
}

// Process a single character in the parser
static int	process_char(t_parser_state *state, const char *input)
{
	char	*temp;

	// Handle variable expansion
	if (input[state->i] == '$' && (!state->in_quotes
			|| state->quote_type == '"'))
	{
		return (handle_variable_expansion(state, input));
	}
	// Handle regular character
	temp = ft_strjoin_char(state->builder, input[state->i]);
	free(state->builder);
	if (!temp)
		return (-1);
	state->builder = temp;
	return (0);
}

int	quote_parser(const char *input, char **tokens, int *i, int *j, int *merge)
{
	t_parser_state state = {.in_quotes = 0, .quote_type = '\0',
		.builder = ft_strdup(""), .i = *i};

	if (!state.builder)
		return (-1);

	// Set initial quote state
	state.quote_type = input[state.i];
	state.in_quotes = 1;
	state.i++;

	// Process characters until end of quote or string
	while (input[state.i])
	{
		if (input[state.i] == state.quote_type)
		{
			state.in_quotes = 0;
			break ;
		}

		if (process_char(&state, input) < 0)
		{
			free(state.builder);
			return (-1);
		}
		state.i++;
	}

	// Check for unterminated quotes
	if (state.in_quotes)
	{
		printf("Error: Unterminated quote\n");
		free(state.builder);
		return (-1);
	}

	state.i++; // Move past closing quote

	// Handle token merging for adjacent quotes
	if (*merge && *j > 0)
	{
		char *temp = ft_strjoin(tokens[*j - 1], state.builder);
		free(tokens[*j - 1]);
		free(state.builder);
		if (!temp)
			return (-1);
		tokens[*j - 1] = temp;
	}
	else
	{
		tokens[(*j)++] = state.builder;
	}

	*i = state.i;
	return (0);
}