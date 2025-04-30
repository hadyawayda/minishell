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

	// If no valid var char next, treat '$' literally
	if (input[*i] == '$' && !(input[*i + 1]
		&& (ft_isalnum(input[*i + 1]) || input[*i + 1] == '_')))
	{
			temp = append_char(*current_token, '$');
			free(*current_token);
			*current_token = temp;
			(*i)++;
			return;
	}

	// Check if we see '$' and there's at least one valid var-name char
	if (input[*i] == '$')
	{
		(*i)++;
		start = *i;
		while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
			(*i)++;
		var_name = ft_substring(input, start, *i);
		if (!var_name)
			return ;
		expanded = expand_variable(var_name);
		free(var_name);
		if (!expanded)
			return ;
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
