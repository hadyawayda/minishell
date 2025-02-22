/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:24:18 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/22 03:52:20 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

int	quote_parser(const char *input, int *i, char **current_token)
{
	char	quote_char;
	char	*temp;

	quote_char = input[*i];
	(*i)++;
	while (input[*i])
	{
		if (input[*i] == quote_char)
		{
			(*i)++;
			return (0);
		}
		if (quote_char == '"' && input[*i] == '$')
			handle_expansion(input, i, current_token);
		else
		{
			temp = append_char(*current_token, input[*i]);
			free(*current_token);
			*current_token = temp;
			(*i)++;
		}
	}
	ft_printf("Unclosed quote detected\n");
	return (-1);
}

// int	quote_parser(const char *input, int *i, char **current_token)
// {
// 	char	quote_char;
// 	quote_char = input[*i];
// 	(*i)++;
// 	while (input[*i])
// 	{
// 		if (input[*i] == quote_char)
// 		{
// 			(*i)++;
// 			return (0);
// 		}
// 		if (quote_char == '"' && input[*i] == '$')
// 			handle_expansion(input, i, current_token);
// 		else
// 			ft_strjoin_char(*current_token, input[*i]);
// 		(*i)++;
// 	}
// 	// ft_printf("unclosed quote\n");
// 	return (0);
// }

// int	quote_parser(const char *input, char **tokens, int *i, int *j)
// {
// 	char	buffer[4096];
// 	int		buf_index;
// 	int		var_start;
// 	char	*var_name;
// 	char	*expanded;
// 	size_t	len;
// 	int		in_quote;
// 	char	quote_type;

// 	buf_index = 0;
// 	in_quote = 0;   // 0 means “not in quotes”
// 	quote_type = 0; // Will be ' or "
// 	// Parse characters until we either finish this token or run out of string
// 	while (input[*i])
// 	{
// 		// 1) If not in quotes and see a ' or ", enter quote mode
// 		if (!in_quote && (input[*i] == '\'' || input[*i] == '"'))
// 		{
// 			// printf("in %s, ascii of current char %c of index %d: %d\n",
// 			// input,
// 			// 	input[*i], *i, input[*i]);
// 			in_quote = 1;
// 			quote_type = input[*i];
// 			(*i)++; // Skip the opening quote
// 		}
// 		// 2) If in quotes and see the matching quote, exit quote mode
// 		else if (in_quote && input[*i] == quote_type)
// 		{
// 			in_quote = 0;
// 			quote_type = 0;
// 			(*i)++; // Skip the closing quote
// 					// If we see a delimiter or end-of-string, token ends here
// 					// printf("in %s, ascii of current char %c of index %d:
// 					// %d\n",
// 					// input,
// 			// 	input[*i], *i, input[*i]);
// 			if (!input[*i] || ft_isdelimiter(input[*i]))
// 				break ;
// 		}
// 		// 3) If we’re not in quotes and see a delimiter, token ends
// 		else if (!in_quote && ft_isdelimiter(input[*i]))
// 		{
// 			// printf("in %s, ascii of current char %c of index %d: %d\n",
// 			// input,
// 			// 	input[*i], *i, input[*i]);
// 			break ;
// 		}
// 		// 4) Check for variable expansion if we’re either outside quotes or in double quotes
// 		//    Single quotes do NOT expand.
// 		else if ((quote_type == '"' || !in_quote) && input[*i] == '$')
// 		{
// 			// printf("in %s, ascii of current char %c of index %d: %d\n",
// 			input,
// 				// 	input[*i], *i, input[*i]);
// 				(*i)++;
// 			var_start = *i;
// 			while (input[*i] != '\0' && (ft_isalnum(input[*i])
// 					|| input[*i] == '_'))
// 				(*i)++;
// 			// If no var name, treat '$' literally (e.g. "$" or "$?")
// 			if (var_start == *i)
// 			{
// 				buffer[buf_index++] = '$';
// 				continue ;
// 			}
// 			// prepend the $ sign to the variable name
// 			var_name = ft_strjoin("$", ft_substring(input, var_start, *i));
// 			if (!var_name)
// 				return (-1);
// 			expanded = expand_variable(var_name);
// 			free(var_name);
// 			if (!expanded)
// 			{
// 				expanded = strdup(""); // Avoid NULL
// 				if (!expanded)
// 					return (-1);
// 			}
// 			len = strlen(expanded);
// 			// Check for buffer overflow
// 			if ((buf_index + (int)len) >= (int)sizeof(buffer))
// 				return (free(expanded), -1); // Too big for our static buffer
// 			ft_strcpy(&buffer[buf_index], expanded);
// 			buf_index += (int)len;
// 			free(expanded);
// 		}
// 		// 5) Otherwise just copy the character into our current token buffer
// 		else
// 		{
// 			// printf("in %s, ascii of current char %c of index %d: %d\n",
// 			input,
// 				// 	input[*i], *i, input[*i]);
// 				buffer[buf_index++] = input[*i];
// 			(*i)++;
// 		}
// 	}
// 	// If we exit and are still in quotes => unclosed quote
// 	if (in_quote)
// 	{
// 		ft_printf("unclosed quote\n");
// 		return (-1); // Caller can print “unclosed quote” error
// 	}
// 	buffer[buf_index] = '\0';
// 	return (0);
// }

// char	*append_char(char *str, char c)
// {
// 	char	*new_str;
// 	int		len;

// 	len = (str) ? ft_strlen(str) : 0;
// 	new_str = malloc(len + 2);
// 	if (!new_str)
// 		return (NULL);
// 	if (str)
// 	{
// 		ft_strcpy(new_str, str);
// 		free(str);
// 	}
// 	new_str[len] = c;
// 	new_str[len + 1] = '\0';
// 	return (new_str);
// }

// int	handle_variable(t_parser_state *state, const char *input,
// char **builder)
// {
// 	char	*expanded;
// 	char	*temp;

// 	if (input[state->i] == '$' && (!state->in_quotes
// 			|| state->quote_type == '"'))
// 	{
// 		expanded = expand_variable(input + state->i);
// 		if (!expanded)
// 			return (-1);
// 		temp = ft_strjoin(*builder ? *builder : "", expanded);
// 		free(expanded);
// 		if (*builder)
// 			free(*builder);
// 		*builder = temp;
// 		while (input[state->i] && !ft_isdelimiter(input[state->i])
// 			&& input[state->i] != '\'' && input[state->i] != '"')
// 			state->i++;
// 		state->i--;
// 		return (1);
// 	}
// 	return (0);
// }

// int	handle_quotes(t_parser_state *state, const char *input)
// {
// 	if (!state->in_quotes)
// 	{
// 		state->in_quotes = 1;
// 		state->quote_type = input[state->i];
// 		return (1);
// 	}
// 	else if (input[state->i] == state->quote_type)
// 	{
// 		state->in_quotes = 0;
// 		state->quote_type = '\0';
// 		return (1);
// 	}
// 	return (0);
// }
