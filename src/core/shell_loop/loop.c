/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:57:01 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/04 18:55:24 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core.h"

void	process_line(t_shell *shell, char *input)
{
	int		i;
	t_token	*tokens;

	i = 0;
	tokens = input_tokenizer(shell, input);
	if (check_syntax(tokens) < 0)
	{
		while (tokens[i].type != (t_tokentype)-1)
			free(tokens[i++].value);
		free(tokens);
		return ;
	}
	// 3) (future) build AST, execute, etc.
	//    t_job *job = parse_tokens(tokens);
	//    execute_job(job);
	//    free_job(job);
	i = 0;
	while (tokens[i].type != (t_tokentype)-1)
		free(tokens[i++].value);
	free(tokens);
}

void	shell_loop(t_shell *shell)
{
	char	*input;

	while (!shell->exit_requested)
	{
		input = readline("\033[0;32mMichel >\033[0m ");
		if (!input)
		{
			ft_printf("exit\n");
			shell->exit_requested = 1;
			break ;
		}
		if (ft_strcmp(input, "exit") == 0)
		{
			ft_printf("exit\n");
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
// 			ft_printf("exit\n");
// 			break ;
// 		}
// 		if (strcmp(input, "exit") == 0)
// 		{
// 			ft_printf("exit\n");
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