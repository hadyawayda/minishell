/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_builtins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 23:45:32 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/05 00:13:46 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/execution.h"

/*
** `env` builtin: list all environment variables (skip NULL values).
*/
int	builtin_env(t_shell *sh, char **argv)
{
	(void)argv;
	list_env(sh->env);
	return (0);
}

/*
** Handle “export KEY[=VALUE] ...” when there are arguments.
** For each argv[i]:
**   - If contains '=', split into key/value, add/update.
**   - Otherwise, add/update with empty string.
*/
static int	process_export_args(t_shell *sh, char **argv)
{
	int		i;
	char	*eq;
	char	*key;
	char	*value;

	i = 1;
	while (argv[i] != NULL)
	{
		eq = ft_strchr(argv[i], '=');
		if (eq != NULL)
		{
			*eq = '\0';
			key = argv[i];
			value = eq + 1;
			add_or_update_env_variable(&sh->env, key, value);
			*eq = '=';
		}
		else
			add_or_update_env_variable(&sh->env, argv[i], "");
		i++;
	}
	return (0);
}

/*
** export [KEY[=VALUE] ...]
**   • No args: print “declare -x KEY...” sorted.
**   • With args: process assignments in process_export_args.
*/
int	builtin_export(t_shell *sh, char **argv)
{
	if (argv[1] == NULL)
	{
		list_export(sh->env);
		return (0);
	}
	return (process_export_args(sh, argv));
}

/*
** `unset KEY ...`: remove each KEY from environment if valid identifier.
*/
int	builtin_unset(t_shell *sh, char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (is_valid_varname(argv[i]))
			unset_env_variable(&sh->env, argv[i]);
		else
			printf("minishell: unset: `%s': not a valid identifier\n", argv[i]);
		i++;
	}
	return (0);
}
