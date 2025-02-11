/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cloner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:31:32 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/11 16:59:51 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core.h"

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
