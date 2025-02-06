/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:55:40 by hawayda           #+#    #+#             */
/*   Updated: 2024/09/28 20:55:52 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Function to execute an AST node
void	execute_ast(t_ast_node *node)
{
	if (!node)
		return ;

	if (node->type == AST_COMMAND)
	{
		// Execute the command using execve or execvp
		pid_t pid = fork();
		if (pid == 0)
		{
			// Child process
			execvp(node->command->argv[0], node->command->argv);
			perror("execvp"); // If execvp fails
			exit(EXIT_FAILURE);
		}
		else
		{
			// Parent process
			waitpid(pid, NULL, 0);
		}
	}
	else if (node->type == AST_PIPE)
	{
		// Set up pipes and execute left and right children
		int pipefd[2];
		pipe(pipefd);

		pid_t pid = fork();
		if (pid == 0)
		{
			// Child process for the left side of the pipe
			dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe write
			close(pipefd[0]);
			execute_ast(node->pipe.left);
			exit(0);
		}
		else
		{
			// Parent process
			waitpid(pid, NULL, 0);
			dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe read
			close(pipefd[1]);
			execute_ast(node->pipe.right);
		}
	}
	else if (node->type == AST_REDIRECTION)
	{
		// Handle redirections
		int fd;
		if (node->redirection.type == REDIR_INPUT)
		{
			fd = open(node->redirection.file, O_RDONLY);
			dup2(fd, STDIN_FILENO);
		}
		else if (node->redirection.type == REDIR_OUTPUT)
		{
			fd = open(node->redirection.file, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			dup2(fd, STDOUT_FILENO);
		}
		else if (node->redirection.type == REDIR_APPEND)
		{
			fd = open(node->redirection.file, O_WRONLY | O_CREAT | O_APPEND,
					0644);
			dup2(fd, STDOUT_FILENO);
		}
		close(fd);
		execute_ast(node->redirection.command_node);
	}
}