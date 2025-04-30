/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:05:30 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/30 12:05:00 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*
** process_echo:
**   Support multiple -n flags and print arguments separated by spaces.
*/
void	process_echo(char **args)
{
	int		i;
	bool	print_nl;

	i = 1;
	print_nl = true;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0
		&& args[i][2] == '\0')
	{
		print_nl = false;
		i++;
	}
	i = 1;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (print_nl)
		printf("\n");
}
