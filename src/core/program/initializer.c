/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:56:41 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/12 22:56:00 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_env	*create_default_env(void)
{
	t_env	*head;

	head = create_env_node("SHLVL", "1");
	head = create_env_node("PWD", "1");
	head = create_env_node("OLDPWD", "1");
	if (!head)
		return (NULL);
	return (head);
}

void	set_shell_shlvl(t_env **env)
{
	char	*shlvl_value;
	char	*new_shlvl;
	int		shlvl;

	shlvl_value = get_env_value(*env, "SHLVL");
	if (shlvl_value && shlvl_value[0] != '\0')
		shlvl = atoi(shlvl_value) + 1;
	else
		shlvl = 1;
	new_shlvl = ft_itoa(shlvl);
	if (!new_shlvl)
		return ;
	if (env_list_contains(*env, "SHLVL"))
		update_env_variable(env, "SHLVL", new_shlvl);
	else
		add_env_variable(env, "SHLVL", new_shlvl);
	free(new_shlvl);
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	if (envp && envp[0])
		shell->env = clone_env(envp);
	else
		shell->env = create_default_env();
	set_shell_shlvl(&shell->env);
	shell->exit_requested = 0;
	shell->last_exit_status = 0;
	return (shell);
}
