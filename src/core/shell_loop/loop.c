/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:57:01 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/13 01:27:55 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core.h"

// Handle cases when SHLVL and path are not created
// Ensure uniqueness of keys in env
// t_env	*increment_shell_level(t_env *_env)
// {
// 	char	*tmp;

// 	tmp = get_node_value_by_key(_env, "SHLVL", (void *)(increment_node(1)));
// 	tmp = ft_itoa(ft_atoi(tmp) + 1);
// 	set_node_value_by_key(_env, "SHLVL", tmp);
// 	return (_env);
// }

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
		parser(shell, input);
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