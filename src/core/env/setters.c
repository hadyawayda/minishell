/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 23:08:57 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/26 00:50:07 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	unset_env_variable(t_env **env, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	is_valid_varname(char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	add_or_update_env_variable(t_env **env, char *key, char *value)
{
	t_env	*current;

	if (!is_valid_varname(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(key, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
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
			return (0);
		}
		current = current->next;
	}
	return (add_env_variable(env, key, value));
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
		{
			free_env(new_head);
			return (NULL);
		}
		if (!new_head)
			new_head = new_node;
		else
			last->next = new_node;
		last = new_node;
		env = env->next;
	}
	return (new_head);
}
