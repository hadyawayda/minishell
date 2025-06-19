/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_builtins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 23:45:32 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/12 22:57:46 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
** `env` builtin: list all environment variables (skip NULL values).
*/
int	builtin_env(t_shell *sh)
{
	while (sh->env)
	{
		if (sh->env->value)
			printf("%s=%s\n", sh->env->key, sh->env->value);
		sh->env = sh->env->next;
	}
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
	int		status;

	i = 1;
	while (argv[i] != NULL)
	{
		eq = ft_strchr(argv[i], '=');
		if (eq != NULL)
		{
			*eq = '\0';
			key = argv[i];
			value = eq + 1;
			status = add_or_update_env_variable(&sh->env, key, value);
			*eq = '=';
		}
		else
			status = add_or_update_env_variable(&sh->env, argv[i], "");
		i++;
	}
	return (status);
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
		if (argv[i][0] == '\0')
			return (0);
		else if (is_valid_varname(argv[i]))
			unset_env_variable(&sh->env, argv[i]);
		else
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
