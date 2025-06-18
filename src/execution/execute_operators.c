/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_operators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:18:04 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/12 22:57:51 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
** For N_AND: if left returns 0, run right; else return left’s status.
*/
int	execute_and(t_shell *shell, t_ast *node)
{
	int	st;

	st = execute_ast(shell, node->left);
	if (st == 0)
		return (execute_ast(shell, node->right));
	return (st);
}

/*
** For N_OR: if left returns nonzero, run right; else return left’s status.
*/
int	execute_or(t_shell *shell, t_ast *node)
{
	int	st;

	st = execute_ast(shell, node->left);
	if (st != 0)
		return (execute_ast(shell, node->right));
	return (st);
}

/*
** Fork and run the LEFT subtree of a PIPE:
**   • In child: redirect stdout → pipefd[1], then exit(execute_ast(left)).
**   • In parent: return child pid, or -1 on fork error.
*/
static pid_t	fork_and_exec_left(t_shell *shell, t_ast *left, int pipefd[])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exit(execute_ast(shell, left));
	}
	return (pid);
}

/*
** Fork and run the RIGHT subtree of a PIPE:
**   • In child: redirect stdin ← pipefd[0], then exit(execute_ast(right)).
**   • In parent: return child pid, or -1 on fork error.
*/
static pid_t	fork_and_exec_right(t_shell *shell, t_ast *right, int pipefd[])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exit(execute_ast(shell, right));
	}
	return (pid);
}

/*
** For a PIPE node:
**   1) Create pipefd[2].
**   2) Fork left child via fork_and_exec_left().
**   3) Fork right child via fork_and_exec_right().
**   4) Parent closes both ends, waits for both children,
**      and returns the right child’s exit status.
*/
int	execute_pipe(t_shell *shell, t_ast *node)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		left_stat;
	int		right_stat;

	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		return (1);
	}
	left_pid = fork_and_exec_left(shell, node->left, pipefd);
	if (left_pid < 0)
		return (1);
	right_pid = fork_and_exec_right(shell, node->right, pipefd);
	if (right_pid < 0)
		return (1);
	close(pipefd[0]);
	close(pipefd[1]);
	ignore_signals();
	waitpid(left_pid, &left_stat, 0);
	waitpid(right_pid, &right_stat, 0);
	setup_signals();
	if (WIFEXITED(right_stat))
		return (WEXITSTATUS(right_stat));
	return (1);
}
