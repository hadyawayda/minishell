/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:56:41 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/26 00:04:38 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	free_shell(t_shell *shell)
{
	if (shell)
	{
		free_env(shell->env);
		free(shell);
	}
}

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

t_env	*create_default_env(void)
{
	t_env	*env;
	char	*pwd;
	char	*path;

	env = NULL;
	pwd = getcwd(NULL, 0);
	path = getenv("PATH");
	if (!pwd)
		pwd = ft_strdup("/");
	if (!path)
		path = "/usr/local/bin:/usr/bin:/bin";
	if (add_env_variable(&env, "SHLVL", "2") || add_env_variable(&env, "PWD",
			pwd) || add_env_variable(&env, "OLDPWD", pwd)
		|| add_env_variable(&env, "PATH", path))
	{
		free(pwd);
		free_env(env);
		return (NULL);
	}
	free(pwd);
	return (env);
}

void	set_shell_shlvl(t_env **env)
{
	char	*shlvl_value;
	char	*new_shlvl;
	int		shlvl;

	shlvl_value = get_env_value(*env, "SHLVL");
	if (shlvl_value && shlvl_value[0] != '\0')
		shlvl = ft_atoi(shlvl_value) + 1;
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
