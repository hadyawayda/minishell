/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:17:56 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/04 20:02:26 by hawayda          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../lib/execution.h"

/*
** Map a command name (string) to its t_builtin value.
** Return BI_NONE if the name does not match any builtin.
*/
t_builtin    get_builtin(char *cmd)
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
** If cmd contains '/', assume it’s a path—duplicate and return it.
** Otherwise, split PATH by ':' and search for an executable file.
** If found, return strdup of the full path. If none found, strdup(cmd).
** Caller must free the returned string.
*/
char    *find_executable(t_shell *sh, char *cmd)
{
    char    **paths;
    char    *pathval;
    char    *prefix;
    char    *full;
    int     i;

    if (ft_strchr(cmd, '/') != NULL)
        return ft_strdup(cmd);

    pathval = get_env_value(sh->env, "PATH");
    if (pathval == NULL || pathval[0] == '\0')
        return ft_strdup(cmd);

    paths = ft_split_charset(pathval, ":");
    if (paths == NULL)
        return ft_strdup(cmd);

    i = 0;
    while (paths[i] != NULL)
    {
        prefix = ft_strjoin(paths[i], "/");
        full = ft_strjoin(prefix, cmd);
        free(prefix);
        if (access(full, X_OK) == 0)
        {
            free_argv(paths);
            return full;
        }
        free(full);
        i++;
    }
    free_argv(paths);
    return ft_strdup(cmd);
}
