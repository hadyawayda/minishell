/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cloners.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:31:32 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/12 23:25:12 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_env	*clone_env(char **envp)
{
	int		i;
	t_env	*head;
	t_env	*current;
	t_env	*new_node;

	head = NULL;
	current = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = parse_env_entry(envp[i]);
		if (!new_node)
			return (NULL);
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}

t_env	*clone_env_list(t_env *env)
{
	t_env	*new_head;
	t_env	*new_node;
	t_env	*last;

	new_head = NULL;
	last = NULL;
	while (env)
	{
		new_node = create_env_node(env->key, env->value);
		if (!new_node)
			return (NULL);
		if (!new_head)
			new_head = new_node;
		else
			last->next = new_node;
		last = new_node;
		env = env->next;
	}
	return (new_head);
}
