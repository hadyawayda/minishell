/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:20:27 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/13 01:08:26 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core.h"

t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = strdup(key);
	if (value)
		new_node->value = strdup(value);
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
