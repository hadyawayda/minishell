/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:11:41 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/21 01:53:00 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

char	*ft_strjoin_char(char *s1, char c)
{
	char	*result;
	size_t	len;

	len = ft_strlen(s1);
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}

char	*expand_variable(const char *str)
{
	char	*result;
	char	*value;
	char	*var_name;
	char	*temp;
	int		i;
	int		start;

	result = ft_strdup(""); // Initialize with empty string
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		// Detect variable expansion
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i
				+ 1] == '_'))
		{
			i++;
			start = i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			var_name = ft_substring(str, start, i);
			if (!var_name)
			{
				free(result);
				return (NULL);
			}
			value = getenv(var_name);
			free(var_name);
			temp = ft_strjoin(result, value ? value : "");
			// Ensuring expansion doesn't return NULL
			free(result);
			result = temp;
			continue ;
		}
		// Append regular character
		temp = ft_strjoin_char(result, str[i]);
		free(result);
		result = temp;
		i++;
	}
	return (result);
}

char	*expand_variable1(const char *str)
{
	int		i;
	int		start;
	char	*result;
	char	*var_name;
	char	*value;
	char	*temp;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && !ft_isspace(str[i + 1]))
		{
			i++;
			start = i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			var_name = ft_substring(str, start, i);
			if (!var_name)
			{
				free(result);
				return (NULL);
			}
			value = getenv(var_name);
			free(var_name);
			if (value)
			{
				temp = ft_strjoin(result, value);
				free(result);
				if (!temp)
					return (NULL);
				result = temp;
			}
			else
			{
				temp = ft_strdup(result);
				free(result);
				if (!temp)
					return (NULL);
			}
			continue ;
		}
		temp = ft_strjoin_char(result, str[i]);
		free(result);
		if (!temp)
			return (NULL);
		result = temp;
		i++;
	}
	return (result);
}
