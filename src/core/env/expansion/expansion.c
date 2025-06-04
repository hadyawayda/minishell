/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:11:41 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/03 17:58:39 by hawayda          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

# include "../../../lib/core.h"

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
		append_variable_value(sh->env, cur, name);
}
