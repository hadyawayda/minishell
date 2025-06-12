/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:53:10 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/12 22:15:12 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/execution.h"

// #include <unistd.h>
// #include <stdlib.h>
// #include <errno.h>
// #include <sys/stat.h>

/* ---------- "$VAR not set" error ---------------------------- */
int	cd_env_error(char *var)
{
	printf("%s", "minishell: cd: ");
	printf("%s", var);
	printf("%s", " not set\n");
	return (1);
}

/* ---------- generic getcwd() failure reporter --------------- */
int	print_getcwd_error(const char *cmd)
{
	const char	*msg1;
	const char	*msg2;

	msg1 = ": error retrieving current directory: getcwd: cannot "
		"access parent directories: ";
	msg2 = "No such file or directory\n";
	write(2, cmd, ft_strlen(cmd));
	write(2, msg1, ft_strlen(msg1));
	write(2, msg2, ft_strlen(msg2));
	return (1);
}

/* ----- duplicate $VAR into *target, set dash when needed ----- */
int	set_target_from_env(char **target, char *var, int *dash, t_env *env)
{
	char	*val;

	val = get_env_value(env, var);
	if (!val)
		return (cd_env_error(var));
	if (dash)
		*dash = 1;
	*target = ft_strdup(val);
	return (*target == NULL);
}
