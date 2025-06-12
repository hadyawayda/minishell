/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:21:22 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/12 22:57:51 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
** Count how many entries are in the linked list `env`.
*/
static int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env;
	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

/*
** Given one t_env node, build a "KEY=VALUE" string.
** Caller must free the returned string.
*/
static char	*make_pair(t_env *entry)
{
	char	*tmpstr;
	char	*pair;

	tmpstr = ft_strjoin(entry->key, "=");
	pair = ft_strjoin(tmpstr, entry->value);
	free(tmpstr);
	return (pair);
}

/*
** Build a NULL-terminated char*[] from shell->env:
** each element is "KEY=VALUE". Caller must free with free_argv().
*/
char	**build_envp(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	int		total;
	int		i;

	total = count_env_vars(env);
	envp = malloc(sizeof(char *) * (total + 1));
	if (envp == NULL)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp != NULL)
	{
		envp[i] = make_pair(tmp);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
