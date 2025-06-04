/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 03:56:48 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/03 18:12:12 by hawayda          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../lib/core.h"

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

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;
	char	*shlvl_value;
	char	*new_shlvl;
	int		shlvl;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	if (envp[0])
		shell->env = clone_env(envp);
	else
		shell->env = create_default_env();
	shlvl_value = get_env_value(shell->env, "SHLVL");
	if (shlvl_value && shlvl_value[0] != '\0')
		shlvl = atoi(shlvl_value) + 1;
	else
		shlvl = 1;
	new_shlvl = ft_itoa(shlvl);
	if (!new_shlvl)
		return (shell);
	if (env_list_contains(shell->env, "SHLVL"))
		update_env_variable(&(shell->env), "SHLVL", new_shlvl);
	else
		add_env_variable(&(shell->env), "SHLVL", new_shlvl);
	free(new_shlvl);
	shell->exit_requested = 0;
	shell->last_exit_status = 0;
	return (shell);
}
