/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:31:57 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/13 01:07:59 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/core.h"

t_env	*create_default_env(void)
{
	t_env	*head;

	head = create_env_node("SHLVL", "1");
	head = create_env_node("PWD", "1");
	head = create_env_node("PATH", "1");
	if (!head)
		return (NULL);
	return (head);
}
