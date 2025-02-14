/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:19:12 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/14 04:44:31 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core.h"

// H<3N
char	*get_env_value(t_env *env, char *key)
{
	if (!key || !env)
		return ("");
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			if (env->value)
				return (env->value);
			else
				return ("");
		env = env->next;
	}
	return ("");
}
char	*expand_variables(char *input, t_shell *shell)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	char	*exit_status_str;
	int		i;
	int		j;
	int		start;

	if (!input)
		return (NULL);
	result = (char *)malloc(4096);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '$' && (i == 0 || input[i - 1] != '\\'))
		{
			if (input[i + 1] == '?')
			{
				exit_status_str = ft_itoa(shell->last_exit_status);
				if (!exit_status_str)
				{
					free(result);
					return (NULL);
				}
				ft_strcpy(&result[j], exit_status_str);
				j += ft_strlen(exit_status_str);
				free(exit_status_str);
				i += 2;
				continue ;
			}
			start = ++i;
			while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
				i++;
			if (i == start)
			{
				result[j++] = '$';
				continue ;
			}
			var_name = ft_strndup(&input[start], i - start);
			if (!var_name)
			{
				free(result);
				return (NULL);
			}
			var_value = get_env_value(shell->env, var_name);
			free(var_name);
			if (var_value)
			{
				ft_strcpy(&result[j], var_value);
				j += ft_strlen(var_value);
			}
		}
		else
		{
			result[j++] = input[i++];
		}
	}
	result[j] = '\0';
	return (result);
}
