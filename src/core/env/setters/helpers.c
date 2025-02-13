/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 03:41:53 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/13 03:53:56 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core.h"

int	env_list_contains(t_env *env, char *key)
{
	if (!env)
		return (0);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	add_env_variable(t_env **env, char *key, char *value)
{
	t_env	*new_node;

	new_node = create_env_node(key, value);
	if (!new_node)
		return ;
	new_node->next = *env;
	*env = new_node;
}

void	update_env_variable(t_env **env, char *key, char *value)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
}