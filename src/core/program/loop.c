/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:55:50 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/05 17:55:50 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/core.h"

void	process_line(t_shell *shell, char *input)
{
	t_token	*tokens;
	t_ast		*root;
	int			status;

	status = 0;
	if (input[0] == '\0' || ft_is_only_whitespace(input) == true)
		return;
	tokens = input_tokenizer(shell, input);
	if (tokens == NULL)
			return;
	root = parser(shell, tokens);
	if (root == NULL)
	{
		free_ast(root);
		return;
	}
	status = execute_ast(shell, root);
	shell->last_exit_status = status;
	free_ast(root);
}

void	shell_loop(t_shell *shell)
{
	char	*input;

	while (!shell->exit_requested)
	{
		input = readline("\033[0;32mMichel >\033[0m ");
		if (!input)
		{
			printf("exit\n");
			shell->exit_requested = 1;
			break ;
		}
		if (ft_strcmp(input, "exit") == 0)
		{
			printf("exit\n");
			free(input);
			shell->exit_requested = 1;
			break ;
		}
		add_history(input);
		process_line(shell, input);
		free(input);
	}
}

// void	shell_loop(char **env)
// {
// 	char *input;

// 	input = NULL;
// 	while (1)
// 	{
// 		input = readline("\033[0;32mMinishell >\033[0m ");
// 		if (input == NULL)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		if (strcmp(input, "exit") == 0)
// 		{
// 			printf("exit\n");
// 			free(input);
// 			break ;
// 		}
// 		// if (g_last_signal != 0)
// 		// {
// 		// 	env_cpy->last_exit_status = 128 + g_last_signal;
// 		// 	g_last_signal = 0;
// 		// }
// 		// check(input, env_cpy);
// 		free(input);
// 	}
// }