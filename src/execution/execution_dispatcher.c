/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_dispatcher.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:18:00 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/13 01:05:27 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

/*
** Called only inside a forked child.
**   - First apply ANY redirections for this node (">", "<", ">>", "<<").
**   - Then either run a builtin in‐process, or do execve()/exit.
*/
void	execute_child_command(t_shell *sh, t_ast *node)
{
	char	**argv;
	char	**envp;
	char	*exec_path;
	int		cb;

	argv = build_argv(node);
	if (argv == NULL)
		exit(1);
	apply_redirections(node->cmd.redirs);
	cb = handle_child_builtin(sh, node, argv);
	if (cb >= 0)
	{
		free_argv(argv);
		exit(cb);
	}
	envp = build_envp(sh->env);
	exec_path = find_executable(sh, argv[0]);
	execve(exec_path, argv, envp);
	free(exec_path);
	printf("minishell: %s: command not found\n", argv[0]);
	if (envp)
		free_argv(envp);
	free_argv(argv);
	exit(127);
}

int	execute_parent_command(t_shell *sh, t_ast *node)
{
	char	**argv;
	int		status;

	status = -1;
	argv = build_argv(node);
	if (argv == NULL)
		return (1);
	if (ft_strcmp(argv[0], "cd") == 0)
		status = builtin_cd(argv, sh->env);
	if (ft_strcmp(argv[0], "exit") == 0)
		status = builtin_exit(argv);
	if (ft_strcmp(argv[0], "unset") == 0)
		status = builtin_unset(sh, argv);
	if (ft_strcmp(argv[0], "export") == 0 && argv[1] != NULL)
		status = builtin_export(sh, argv);
	free_argv(argv);
	return (status);
}

/*
** For a single N_CMD node when NOT in a pipeline, we still fork once
** so that builtins and execve happen in the child. The parent only waits.
*/
int	execute_cmd(t_shell *shell, t_ast *node)
{
	pid_t	pid;
	int		wstatus;

	wstatus = execute_parent_command(shell, node);
	if (wstatus >= 0)
		return (wstatus);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
		execute_child_command(shell, node);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
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
