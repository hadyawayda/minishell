/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:06:00 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/28 14:01:55 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <stdlib.h>

int	main(int argc, char *argv[], char *envp[])
{
	char	**args;

	if (argc > 1 && strcmp(argv[1], "-c") == 0 && argc > 2)
	{
		args = split_input(argv[2]);
		if (args != NULL && args[0] != NULL)
		{
			if (is_builtin(args[0]))
				execute_builtin(args, envp);
			else
				execute_command(args);
		}
		free(args);
	}
	else
		start_shell(envp);
	return (0);
}
