/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:11:41 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/04 03:31:28 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	handle_expansion(t_shell *sh, const char *in, int *i, char **cur)
{
	char	*name;
	char	*value;
	char	*tmp;
	int		start;
	char	*nbr;

	if (in[*i] != '$')
		return ;
	if (in[*i + 1] == '?')
	{
		nbr = ft_itoa(sh->last_exit_status);
		tmp = ft_strjoin(*cur, nbr);
		free(nbr);
		free(*cur);
		*cur = tmp;
		(*i) += 2;
		return ;
	}
	if (in[*i + 1] == '$')
	{
		append_char_inplace(cur, '$', i);
		append_char_inplace(cur, '$', i);
		return ;
	}
	if (!(ft_isalpha(in[*i + 1]) || in[*i + 1] == '_' || ft_isdigit(in[*i
				+ 1])))
	{
		append_char_inplace(cur, '$', i);
		return ;
	}
	(*i)++;
	start = *i;
	if (ft_isdigit(in[*i]))
		(*i)++;
	else
		while (ft_isalnum(in[*i]) || in[*i] == '_')
			(*i)++;
	name = ft_substring(in, start, *i);
	if (!name)
		return ;
	value = expand_variable(name);
	free(name);
	if (!value)
		return ;
	tmp = ft_strjoin(*cur, value);
	free(value);
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
