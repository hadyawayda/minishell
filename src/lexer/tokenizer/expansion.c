/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:11:41 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/18 19:30:00 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

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
			result = ft_strjoin_and_free(result, ft_substring(input, start, i
						+ 1));
			i++;
		}
		else if (input[i] == '$' && input[i + 1] && (ft_isalnum(input[i + 1])
				|| input[i + 1] == '_'))
		{
			start = ++i;
			while (ft_isalnum(input[i]) || input[i] == '_')
				i++;
			var_name = ft_substring(input, start, i);
			var_value = getenv(var_name);
			temp = var_value ? ft_strdup(var_value) : ft_strdup("");
			result = ft_strjoin_and_free(result, temp);
			free(var_name);
		}
		else
		{
			temp = ft_substring(input, i, i + 1);
			result = ft_strjoin_and_free(result, temp);
			i++;
		}
	}
	return (result);
}
