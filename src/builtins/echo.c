/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:05:30 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/05 13:50:21 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* returns true if s is exactly "-n", "-nn", "-nnn", etc */
static bool	is_n_flag(char *s)
{
	int	i;

	if (!s || s[0] != '-')
		return (false);
	i = 1;
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

/* print token, but treat "\n" as literal 'n' */
static void	print_arg(char *s)
{
	if (ft_strcmp(s, "\\n") == 0)
		printf("n");
	else
		printf("%s", s);
}

/*
** process_echo:
**   Skip any number of -n flags, print the rest separated by spaces,
**   and only add a trailing newline if no -n was seen.
*/
void	process_echo(char **args)
{
	int		i;
	bool	print_nl;

	i = 1;
	print_nl = true;
	while (is_n_flag(args[i]))
	{
		print_nl = false;
		i++;
	}
	while (args[i])
	{
		print_arg(args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (print_nl)
		printf("\n");
}
