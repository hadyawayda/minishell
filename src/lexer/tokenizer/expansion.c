/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:11:41 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/04 17:53:30 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

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

void	append_variable_value(char **cur, char *name)
{
	char	*env;
	char	*val;
	char	*tmp;

	env = getenv(name);
	free(name);
	if (env)
		val = ft_strdup(env);
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
	if (in[*i + 1] == '?')
	{
		append_exit_status(sh, i, cur);
		return ;
	}
	if (in[*i + 1] == '$')
	{
		append_literal_dollars(in, i, cur);
		return ;
	}
	if (!(ft_isalpha(in[*i + 1]) || in[*i + 1] == '_' || ft_isdigit(in[*i
					+ 1])))
	{
		append_char_inplace(cur, '$', i);
		return ;
	}
	name = parse_var_name(in, i);
	if (name)
		append_variable_value(cur, name);
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
