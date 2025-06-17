/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:56:46 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/17 03:04:29 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	minishell(char **envp)
{
	t_shell	*shell;

	shell = init_shell(envp);
	if (!shell)
	{
		perror("minishell: failed to initialize");
		return ;
	}
	init_main_signals();
	shell_loop(shell);
	free_shell(shell);
	rl_clear_history();
}

// free(input);
// free_env_list(env_cpy);
// rl_free_line_state();
// rl_cleanup_after_signal();
// history_truncate_file(NULL, 0);