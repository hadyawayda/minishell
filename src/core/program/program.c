/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:56:46 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/26 00:04:39 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	process_line(t_shell *shell, char *input)
{
	t_token	*tokens;
	t_ast	*root;
	int		status;

	status = 0;
	if (input[0] == '\0' || ft_is_only_whitespace(input) == true)
		return ;
	tokens = input_tokenizer(shell, input);
	if (tokens == NULL)
		return ;
	root = parser(shell, tokens);
	if (root == NULL)
	{
		free_ast(root);
		return ;
	}
	status = execute_ast(shell, root);
	shell->last_exit_status = status;
	free_ast(root);
}

char	*get_shell_input(t_shell *shell)
{
	char	*input;

	input = readline("\033[0;32mMichel > \033[0m");
	if (!input)
	{
		printf("exit\n");
		shell->exit_requested = 1;
		return (NULL);
	}
	if (ft_strcmp(input, "exit") == 0)
	{
		printf("exit\n");
		free(input);
		shell->exit_requested = 1;
		return (NULL);
	}
	return (input);
}

void	execute_shell_input(t_shell *shell, char *input)
{
	add_history(input);
	if (g_last_signal != 0)
	{
		shell->last_exit_status = 128 + g_last_signal;
		g_last_signal = 0;
	}
	process_line(shell, input);
}

void	shell_loop(t_shell *shell)
{
	char	*input;

	while (!shell->exit_requested)
	{
		input = get_shell_input(shell);
		if (!input)
			break ;
		execute_shell_input(shell, input);
		free(input);
	}
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
	setup_signals();
	shell_loop(shell);
	free_shell(shell);
	rl_clear_history();
}
