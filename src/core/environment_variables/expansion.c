/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:19:12 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/12 04:38:08 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core.h"

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return ("");
}

char	*expand_variables(char *input, t_env *env)
{
	char	*result;
	int		i;
	int		j;
	int		len;
	int		start;
	char	*var_name;
	char	*var_value;

	i = 0;
	j = 0;
	len = strlen(input);
	result = (char *)malloc(len * 2);
	if (!result)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '$' && (i == 0 || input[i - 1] != '\\'))
		{
			start = ++i;
			while (input[i] && (isalnum(input[i]) || input[i] == '_'))
				i++;
			var_name = strndup(&input[start], i - start);
			var_value = get_env_value(env, var_name);
			free(var_name);
			strcpy(&result[j], var_value);
			j += strlen(var_value);
		}
		else
		{
			result[j++] = input[i++];
		}
	}
	result[j] = '\0';
	return (result);
}
