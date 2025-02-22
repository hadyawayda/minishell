/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:11:41 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/22 04:00:40 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	handle_expansion(const char *input, int *i, char **current_token)
{
	char	*expanded;
	char	*temp;
	char	*var_name;
	int		start;

	if (!input || !i || !current_token || !*current_token)
		return ;
	// Check if we see '$' and there's at least one valid var-name char
	if (input[*i] == '$' && input[*i + 1] && (ft_isalnum(input[*i + 1])
			|| input[*i + 1] == '_'))
	{
		(*i)++;     // Move past '$'
		start = *i; // Start of variable name
		// Collect alnum and underscores for var_name
		while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
			(*i)++;
		var_name = ft_substring(input, start, *i);
		if (!var_name)
			return ;
		// Fetch its value from the environment
		expanded = expand_variable(var_name);
		free(var_name);
		if (!expanded)
			return ;
		// Append the expanded string to current_token
		temp = ft_strjoin(*current_token, expanded);
		free(expanded);
		free(*current_token);
		*current_token = temp;
	}
}

char	*expand_variable(const char *var_name)
{
	char	*env_value;

	if (!var_name)
		return (NULL);
	env_value = getenv(var_name);
	if (!env_value)
		return (ft_strdup(""));
	return (ft_strdup(env_value));
}

// char	*expand_variable1(const char *str)
// {
// 	int		i;
// 	int		start;
// 	char	*result;
// 	char	*var_name;
// 	char	*value;
// 	char	*temp;
// 	result = ft_strdup("");
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1] && !ft_isspace(str[i + 1]))
// 		{
// 			i++;
// 			start = i;
// 			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
// 				i++;
// 			var_name = ft_substring(str, start, i);
// 			if (!var_name)
// 			{
// 				free(result);
// 				return (NULL);
// 			}
// 			value = getenv(var_name);
// 			free(var_name);
// 			if (value)
// 			{
// 				temp = ft_strjoin(result, value);
// 				free(result);
// 				if (!temp)
// 					return (NULL);
// 				result = temp;
// 			}
// 			else
// 			{
// 				temp = ft_strdup(result);
// 				free(result);
// 				if (!temp)
// 					return (NULL);
// 			}
// 			continue ;
// 		}
// 		temp = ft_strjoin_char(result, str[i]);
// 		free(result);
// 		if (!temp)
// 			return (NULL);
// 		result = temp;
// 		i++;
// 	}
// 	return (result);
// }
