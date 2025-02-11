/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:21:59 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/11 18:28:10 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core.h"

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
    if (envp[0])
        shell->env = clone_env(envp);
    else
        shell->env = create_default_env();
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
	shell_loop(shell);
	free_shell(shell);
}

// _env = increment_shell_level(_env);
// setup_signal_handlers();
// free(input);
// free_env_list(env_cpy);
// rl_clear_history();
// rl_free_line_state();
// rl_cleanup_after_signal();
// clear_history();
// history_truncate_file(NULL, 0);