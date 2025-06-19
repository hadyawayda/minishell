/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:56:31 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/19 22:43:39 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_env	*parse_env_entry(char *env_entry)
{
	char	*delimiter;
	t_env	*node;

	delimiter = strchr(env_entry, '=');
	if (!delimiter)
		return (NULL);
	*delimiter = '\0';
	node = create_env_node(env_entry, delimiter + 1);
	*delimiter = '=';
	return (node);
}

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

int	add_env_variable(t_env **env, char *key, char *value)
{
	t_env	*new_node;

	new_node = create_env_node(key, value);
	if (!new_node)
		return (1);
	new_node->next = *env;
	*env = new_node;
	return (0);
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
			if (value != NULL)
				current->value = ft_strdup(value);
			else
				current->value = NULL;
			return ;
		}
		current = current->next;
	}
}
