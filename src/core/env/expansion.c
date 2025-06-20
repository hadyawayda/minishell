/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:56:37 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/20 22:09:58 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

char	*get_env_value(t_env *env, char *key)
{
	if (!key || !env)
		return ("");
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			if (env->value)
				return (env->value);
			else
				return ("");
		}
		env = env->next;
	}
	return ("");
}

void	append_exit_status(t_shell *sh, int *i, char **cur)
{
	char	*nbr;
	char	*tmp;

	nbr = ft_itoa(sh->last_exit_status);
	tmp = ft_strjoin(*cur, nbr);
	free(nbr);
	free(*cur);
	*cur = tmp;
	*i += 2;
}

char	*parse_var_name(const char *in, int *i)
{
	int	start;

	start = ++(*i);
	if (ft_isdigit(in[*i]))
		(*i)++;
	else
		while (ft_isalnum(in[*i]) || in[*i] == '_')
			(*i)++;
	return (ft_substring(in, start, *i));
}

void	append_variable_value(t_env *env, char **cur, char *name)
{
	char	*env_val;
	char	*val;
	char	*tmp;

	env_val = get_env_value(env, name);
	free(name);
	if (env_val)
		val = ft_strdup(env_val);
	else
		val = ft_strdup("");
	tmp = ft_strjoin(*cur, val);
	free(val);
	free(*cur);
	*cur = tmp;
}

void	handle_expansion(t_shell *sh, const char *in, int *i, char **cur)
{
	char	*name;

	if (in[*i] != '$')
		return ;
	if (in[*i + 1] == '*')
	{
		*i += 2;
		return ;
	}
	if (in[*i + 1] == '?')
		return (append_exit_status(sh, i, cur));
	if (in[*i + 1] == '$')
		return (append_literal_dollars(in, i, cur));
	if (!(ft_isalpha(in[*i + 1]) || in[*i + 1] == '_' || ft_isdigit(in[*i
					+ 1])))
		return (append_char_inplace(cur, '$', i));
	name = parse_var_name(in, i);
	if (name)
		append_variable_value(sh->env, cur, name);
}
