/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:17:56 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/16 23:40:31 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

/*
** Child‐side builtins: printing commands handled here.
** Return >=0 if handled, else –1 so we’ll execve().
*/
int	handle_child_builtin(t_shell *shell, t_ast *node, char **argv)
{
	if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env(shell));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd(argv));
	if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(node, argv));
	if (ft_strcmp(argv[0], "export") == 0 && argv[1] == NULL)
		return (builtin_export(shell, argv));
	return (-1);
}

/*–– after execve() fails, print error, free, and exit ––*/
void	exec_error_and_exit(char *exec_path, char **argv, char **envp)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putstr_fd(": ", 2);
	if (ft_strchr(argv[0], '/'))
		ft_putstr_fd(strerror(errno), 2);
	else
		ft_putstr_fd("command not found", 2);
	ft_putstr_fd("\n", 2);
	free(exec_path);
	if (envp)
		free_argv(envp);
	free_argv(argv);
	exit(127);
}
