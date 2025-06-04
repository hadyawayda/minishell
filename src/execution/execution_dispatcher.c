/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_dispatcher.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:18:00 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/05 00:38:51 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/execution.h"

/*
** If argv[0] is a recognized builtin, run it and return its exit status.
** Otherwise, return −1 to signal “not a builtin.”
*/
int	handle_builtin(t_shell *sh, char **argv)
{
	int	status;

	// if (ft_strcmp(argv[0], "cd") == 0)
	// 	status = builtin_cd(sh, argv);
	// else if (ft_strcmp(argv[0], "pwd") == 0)
	// 	status = builtin_pwd(sh, argv);
	// else if (ft_strcmp(argv[0], "echo") == 0)
	// 	status = builtin_echo(sh, argv);
	// else if (ft_strcmp(argv[0], "exit") == 0)
	// 	status = builtin_exit(sh, argv);
	// else
	// 	return (-1);
	return (status);
}

/*
** Called only inside a forked child.
**   - First apply ANY redirections for this node (">", "<", ">>", "<<").
**   - Then either run a builtin in‐process, or do execve()/exit.
** Note: sys-builtins (like /bin/echo) are covered by execve;
** your “custom builtins” get integrated here.
*/
void	exec_cmd_in_child(t_shell *sh, t_ast *node)
{
	char	**argv;
	char	**envp;
	int		status;
	char	*exec_path;

	argv = build_argv(node);
	if (argv == NULL)
		exit(1);
	apply_redirections(node->cmd.redirs);
	// status = handle_builtin(sh, argv);
	// if (status >= 0)
	// 	exit(status);
	envp = build_envp(sh->env);
	exec_path = find_executable(sh, argv[0]);
	execve(exec_path, argv, envp);
	free(exec_path);
	ft_putstr_fd(argv[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	if (envp)
		free_argv(envp);
	free_argv(argv);
	exit(127);
}

/*
** If argv[0] is "export", "unset", or "cd", run that builtin in the parent.
** Return its exit status. Otherwise, return
	-1 to signal “not a parent-side builtin.”
*/
int	run_parent_builtin(t_shell *shell, char **argv)
{
	int	status;

	if (ft_strcmp(argv[0], "env") == 0)
		status = builtin_env(shell, argv);
	else if (ft_strcmp(argv[0], "export") == 0)
		status = builtin_export(shell, argv);
	else if (ft_strcmp(argv[0], "unset") == 0)
		status = builtin_unset(shell, argv);
	else
		return (-1);
	return (status);
}

/*
** For a single N_CMD node when NOT in a pipeline, we still fork once
** so that builtins and execve happen in the child. The parent only waits.
*/
int	execute_cmd(t_shell *shell, t_ast *node)
{
	char	**argv;
	pid_t	pid;
	int		wstatus;

	argv = build_argv(node);
	if (argv == NULL)
		return (1);
	wstatus = run_parent_builtin(shell, argv);
	if (wstatus >= 0)
	{
		free_argv(argv);
		return (wstatus);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
		exec_cmd_in_child(shell, node);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		return (free_argv(argv), WEXITSTATUS(wstatus));
	return (1);
}

/*
** Walk the AST. For each node,
** call the appropriate function and recurse back appropriately.
*/
int	execute_ast(t_shell *shell, t_ast *node)
{
	if (node == NULL)
		return (0);
	if (node->type == N_CMD)
		return (execute_cmd(shell, node));
	else if (node->type == N_PIPE)
		return (execute_pipe(shell, node));
	else if (node->type == N_AND)
		return (execute_and(shell, node));
	else if (node->type == N_OR)
		return (execute_or(shell, node));
	return (0);
}
