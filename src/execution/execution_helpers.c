/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:17:56 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/04 23:10:42 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/execution.h"

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
