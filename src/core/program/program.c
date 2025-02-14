/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:21:59 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/14 03:43:29 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core.h"

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

void	minishell(char **envp)
{
	t_shell	*shell;

	shell = init_shell(envp);
	if (!shell)
	{
		perror("minishell: failed to initialize");
		return ;
	}
	setup_signal_handlers();
	shell_loop(shell);
	free_shell(shell);
	rl_clear_history();
}

// free(input);
// free_env_list(env_cpy);
// rl_free_line_state();
// rl_cleanup_after_signal();
// history_truncate_file(NULL, 0);