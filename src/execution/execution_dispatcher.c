/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_dispatcher.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:18:00 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/17 23:44:07 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
	exec_error_and_exit(exec_path, argv, envp);
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
 * If this node has *only* redirections (no actual command),
 * fork/apply them and return their exit status (0 on success).
 * Otherwise return –1 to signal “not a pure-redir node.”
 */
static int	handle_redir_only(t_ast *node)
{
	pid_t	pid;
	int		st;

	if (node->cmd.command != NULL)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		apply_redirections(node->cmd.redirs);
		exit(0);
	}
	waitpid(pid, &st, 0);
	if (WIFEXITED(st))
		return (WEXITSTATUS(st));
	if (WIFSIGNALED(st))
		return (128 + WTERMSIG(st));
	return (1);
}

/*
 * The main dispatcher for a simple command:
 * 1) Try pure-redirs (>,<,>>,<< with no command).
 * 2) Run any parent-side builtin.
 * 3) Fork & run the child-side builtin or external.
 */
int	execute_cmd(t_shell *shell, t_ast *node)
{
	pid_t	pid;
	int		wstatus;

	wstatus = handle_redir_only(node);
	if (wstatus >= 0)
		return (wstatus);
	wstatus = execute_parent_command(shell, node);
	if (wstatus >= 0)
		return (wstatus);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
		execute_child_command(shell, node);
	ignore_signals();
	waitpid(pid, &wstatus, 0);
	setup_signals();
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
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
