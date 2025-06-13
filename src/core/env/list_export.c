/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 00:03:11 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/12 22:55:54 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	list_export(t_env *env)
{
	t_env	*sorted_env;
	t_env	*temp;

	sorted_env = clone_env_list(env);
	if (!sorted_env)
		return ;
	sort_env_list(&sorted_env);
	temp = sorted_env;
	while (sorted_env)
	{
		if (ft_strcmp(sorted_env->key, "_") == 0)
		{
			sorted_env = sorted_env->next;
			continue ;
		}
		printf("declare -x %s", sorted_env->key);
		if (sorted_env->value)
			printf("=\"%s\"", sorted_env->value);
		printf("\n");
		sorted_env = sorted_env->next;
	}
	free_env(temp);
}
