/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 02:38:42 by hawayda           #+#    #+#             */
/*   Updated: 2024/09/27 05:56:12 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Handle cases when SHLVL and path are not created
// Ensure uniqueness of keys in env
t_env	*increment_shell_level(t_env *_env)
{
	char	*tmp;

	tmp = get_node_value_by_key(_env, "SHLVL", (void *)(increment_node(1)));
	tmp = ft_itoa(ft_atoi(tmp) + 1);
	set_node_value_by_key(_env, "SHLVL", tmp);
	return (_env);
}

void	fsh(char *input, data *_env)
{
	while (1)
	{
		input = readline("\033[0;32mMinishell >\033[0m ");
		if (input == NULL)
		{
			ft_printf("exit\n");
			break ;
		}
		if (strcmp(input, "exit") == 0)
		{
			ft_printf("exit\n");
			free(input);
			break ;
		}
		// if (g_last_signal != 0)
		// {
		// 	env_cpy->last_exit_status = 128 + g_last_signal;
		// 	g_last_signal = 0;
		// }
		// check(input, env_cpy);
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_env	*_env;

	(void)ac;
	(void)av;
	input = NULL;
	setup_signal_handlers();
	// if (env[0] == NULL)
	// 	env_cpy = create_env();
	// else
	// 	env_cpy = clone_env(env);
	_env = increment_shell_level(_env);
	fsh(input, _env);
	free(input);
	// free_env_list(env_cpy);
	rl_clear_history();
	rl_free_line_state();
	rl_cleanup_after_signal();
	clear_history();
	history_truncate_file(NULL, 0);
	return (0);
}
