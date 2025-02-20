/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 03:40:52 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/20 04:02:17 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core.h"

void	non_interactive_processor(t_shell *shell, char **av)
{
	char	*input;

	if (av[1] != NULL)
	{
		input = strdup(av[1]);
		if (!input)
		{
			perror("minishell: memory allocation failed");
			shell->exit_requested = 1;
			return ;
		}
		if (!input)
		{
			ft_printf("exit\n");
			shell->exit_requested = 1;
		}
		if (ft_strcmp(input, "exit") == 0)
		{
			ft_printf("exit\n");
			free(input);
			shell->exit_requested = 1;
		}
		add_history(input);
		parser(shell, input);
		shell->exit_requested = 1;
		free(input);
	}
}

void	non_interactive_minishell(char **av, char **envp)
{
	t_shell	*shell;

	shell = init_shell(envp);
	if (!shell)
	{
		perror("minishell: failed to initialize");
		return ;
	}
	setup_signal_handlers();
	non_interactive_processor(shell, av);
	free_shell(shell);
	rl_clear_history();
}
