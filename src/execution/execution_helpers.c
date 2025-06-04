/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:17:56 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/04 22:27:09 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/execution.h"

/*
** Map a command name (string) to its t_builtin value.
** Return BI_NONE if the name does not match any builtin.
*/
t_builtin	get_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (BI_CD);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (BI_PWD);
	if (ft_strcmp(cmd, "echo") == 0)
		return (BI_ECHO);
	if (ft_strcmp(cmd, "env") == 0)
		return (BI_ENV);
	if (ft_strcmp(cmd, "export") == 0)
		return (BI_EXPORT);
	if (ft_strcmp(cmd, "unset") == 0)
		return (BI_UNSET);
	if (ft_strcmp(cmd, "exit") == 0)
		return (BI_EXIT);
	return (BI_NONE);
}

/*
** Iterate over each element in `paths[]`, join with `"/" + cmd"`, and
** return the first concatenated string whose access(..., X_OK) == 0.
** If none found, return NULL. Caller must free the returned string.
*/
char	*search_paths(char **paths, char *cmd)
{
	char	*prefix;
	char	*full;
	int		i;

	i = 0;
	while (paths[i] != NULL)
	{
		prefix = ft_strjoin(paths[i], "/");
		full = ft_strjoin(prefix, cmd);
		free(prefix);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}

/* Free a null-terminated array of strings */
void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL)
		return ;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

/*
** If `cmd` contains '/', assume it’s a path and return strdup(cmd).
** Otherwise, split PATH by ':' into `paths[]`, call `search_paths()`.
** If `search_paths` returns non-NULL, free `paths[]` and return it.
** If no executable found, free `paths[]` and return strdup(cmd).
*/
char	*find_executable(t_shell *sh, char *cmd)
{
	char	**paths;
	char	*pathval;
	char	*found;

	if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup(cmd));
	pathval = get_env_value(sh->env, "PATH");
	if (pathval == NULL || pathval[0] == '\0')
		return (ft_strdup(cmd));
	paths = ft_split_charset(pathval, ":");
	if (paths == NULL)
		return (ft_strdup(cmd));
	found = search_paths(paths, cmd);
	free_argv(paths);
	if (found != NULL)
		return (found);
	return (ft_strdup(cmd));
}
