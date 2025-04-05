/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:05:41 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/05 21:21:59 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/wait.h>

// change logic to check enum
int	is_builtin(char *command)
{
	return (ft_strcmp(command, "echo") == 0 || ft_strcmp(command, "cd") == 0);
}

int	execute_builtin(char **args, char *envp[])
{
	if (!args[0])
		return (-1);
	if (ft_strcmp(args[0], "echo") == 0)
	{
		process_echo(args);
		return (0);
	}
	else if (ft_strcmp(args[0], "cd") == 0)
	{
		return (process_cd(args, envp)); // ✅ This must return int
	}
	return (-1);
}

int	execute_command(char **args)
{
	pid_t	pid;
	int		status;

	if (!args[0])
	{
		return (-1); // Return error code if no command is provided
	}
	// Detect incorrect command names starting with "echo" but not exactly "echo"
	if (ft_strncmp(args[0], "echo", 4) == 0 && args[0][4] != '\0')
	{
		fprintf(stderr, "bash: %s: command not found\n", args[0]);
		return (-1); // Return error code for incorrect command
	}
	pid = fork();
	if (pid == 0)
	{
		// Child process
		if (execvp(args[0], args) == -1)
		{
			// If execvp fails
			fprintf(stderr, "bash: %s: command not found\n", args[0]);
			exit(127); // Exit with 127 if command not found
		}
	}
	else if (pid > 0)
	{
		// Parent process
		waitpid(pid, &status, 0);
		// Optionally handle child process exit status here (if needed)
		if (WIFEXITED(status))
		{
			return (WEXITSTATUS(status));
			// Return the exit status of the child process
		}
	}
	else
	{
		perror("fork"); // Error for failed fork
		return (-1);    // Return error code if fork fails
	}
	return (0); // Return success if command executed successfully
}

void	start_shell(char *envp[])
{
	char	*input;
	char	**args;

	input = NULL;
	args = NULL;
	while (1)
	{
		input = readline("> "); // Get user input
		if (!input)             // Check for EOF (Ctrl+D)
			break ;
		if (strlen(input) == 0)
		{ // Ignore empty input
			free(input);
			continue ;
		}
		add_history(input);        // Add input to history
		args = split_input(input); // Parse input into args
		if (args[0])
		{
			if (ft_strcmp(args[0], "exit") == 0)
			{ // Handle `exit` command
				free(input);
				free(args);
				break ;
			}
			if (is_builtin(args[0]))
			{                                // Run built-in commands
				execute_builtin(args, envp); // Pass envp
			}
			else
			{
				execute_command(args);
			}
		}
		free(input);
		free(args);
	}
}
