/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:17:54 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/12 22:57:51 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
** Count how many entries in the NULL-terminated options array.
*/
static int	count_options(char **options)
{
	int	n;

	n = 0;
	while (options[n] != NULL)
		n++;
	return (n);
}

/*
** Count how many t_argnode entries in the linked list.
*/
static int	count_args(t_argnode *args)
{
	int	n;

	n = 0;
	while (args != NULL)
	{
		n++;
		args = args->next;
	}
	return (n);
}

/*
** Copy each option string into argv at index *idx, incrementing *idx.
*/
static void	fill_options(char **argv, char **options, int *idx)
{
	int	j;

	j = 0;
	while (options[j] != NULL)
	{
		argv[*idx] = ft_strdup(options[j]);
		(*idx)++;
		j++;
	}
}

/*
** Copy each argument value into argv at index *idx, incrementing *idx.
*/
static void	fill_args(char **argv, t_argnode *args, int *idx)
{
	while (args != NULL)
	{
		argv[*idx] = ft_strdup(args->value);
		(*idx)++;
		args = args->next;
	}
}

/*
** Build a NULL-terminated char*[] from node->cmd.command,
** node->cmd.options[], and the linked list node->cmd.args.
*/
char	**build_argv(t_ast *node)
{
	char	**argv;
	int		nopt;
	int		nargs;
	int		total;
	int		i;

	if (node->cmd.command == NULL)
		return (NULL);
	nopt = count_options(node->cmd.options);
	nargs = count_args(node->cmd.args);
	total = 1 + nopt + nargs + 1;
	argv = malloc(sizeof(char *) * total);
	if (argv == NULL)
		return (NULL);
	i = 0;
	argv[i] = ft_strdup(node->cmd.command);
	i++;
	fill_options(argv, node->cmd.options, &i);
	fill_args(argv, node->cmd.args, &i);
	argv[i] = NULL;
	return (argv);
}
