/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 00:03:15 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/13 01:25:29 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core.h"

t_env	*merge_sorted_env(t_env *left, t_env *right)
{
	t_env	*result;

	result = NULL;
	if (!left)
		return (right);
	if (!right)
		return (left);
	if (ft_strcmp(left->key, right->key) < 0)
	{
		result = left;
		result->next = merge_sorted_env(left->next, right);
	}
	else
	{
		result = right;
		result->next = merge_sorted_env(left, right->next);
	}
	return (result);
}

void	split_env_list(t_env *source, t_env **front, t_env **back)
{
	t_env	*slow;
	t_env	*fast;

	slow = source;
	fast = source->next;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	*front = source;
	*back = slow->next;
	slow->next = NULL;
}

void	sort_env_list(t_env **env)
{
	t_env	*head;
	t_env	*left;
	t_env	*right;

	head = *env;
	if (!head || !head->next)
		return ;
	split_env_list(head, &left, &right);
	sort_env_list(&left);
	sort_env_list(&right);
	*env = merge_sorted_env(left, right);
}
