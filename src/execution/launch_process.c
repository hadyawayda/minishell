/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:18:13 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/04 12:57:41 by hawayda          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../lib/execution.h"

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

/*
** Fork/exec with execve(). We first resolve the executable path,
** then fork. In the child, apply redirs, build envp, and call execve().
** Parent waits and returns the child's exit code.
*/
int    launch_external(t_shell *sh, char **argv, t_redir *redirs)
{
    pid_t   pid;
    int     wstatus;
    char    *exec_path;
    char    **envp;

    exec_path = find_executable(sh, argv[0]);
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        free(exec_path);
        return 1;
    }
    else if (pid == 0)
    {
        apply_redirections(redirs);
        envp = build_envp(sh->env);
        execve(exec_path, argv, envp);
        ft_putstr_fd(argv[0], STDERR_FILENO);
        ft_putstr_fd(": command not found\n", STDERR_FILENO);
        if (envp != NULL)
            free_argv(envp);
        free(exec_path);
        exit(127);
    }
    free(exec_path);
    waitpid(pid, &wstatus, 0);
    if (WIFEXITED(wstatus))
        return WEXITSTATUS(wstatus);
    return 1;
}
