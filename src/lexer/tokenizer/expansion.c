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

/* expansion.c */

void handle_expansion(const char *in, int *i, char **cur)
{
    char *var_name;
    char *expanded;
    char *tmp;
    int   start;

    if (in[*i] != '$')
        return;
    if (!(in[*i + 1] && (ft_isalpha(in[*i + 1]) || in[*i + 1] == '_' || ft_isdigit(in[*i + 1]))))
    {
        *cur = append_char(*cur, '$');
        (*i)++;
        return;
    }
    (*i)++;
    start = *i;
    if (ft_isdigit(in[*i]))
        (*i)++;
    else
        while (in[*i] && (ft_isalnum(in[*i]) || in[*i] == '_'))
            (*i)++;
    var_name = ft_substring(in, start, *i);
    if (!var_name) return;
    expanded = expand_variable(var_name);
    free(var_name);
    if (!expanded) return;
    tmp  = ft_strjoin(*cur, expanded);
    free(expanded);
    free(*cur);
    *cur = tmp;
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
