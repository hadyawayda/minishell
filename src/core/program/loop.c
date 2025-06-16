/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:55:50 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/17 01:52:49 by hawayda          ###   ########.fr       */
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

void	shell_loop(t_shell *shell)
{
	char		*input;
	char		prompt[64];
	const char	*color;

	while (!shell->exit_requested)
	{
		if (shell->last_exit_status == 0)
			color = "\033[0;32m";
		else
			color = "\033[0;31m";
		ft_strlcpy(prompt, color, sizeof(prompt));
		ft_strlcat(prompt, "Michel >", sizeof(prompt));
		ft_strlcat(prompt, "\033[0m ", sizeof(prompt));
		input = readline(prompt);
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
		if (g_last_signal != 0)
		{
			shell->last_exit_status = 128 + g_last_signal;
			g_last_signal = 0;
			free(input);
			continue ;
		}
		process_line(shell, input);
		free(input);
	}
}
