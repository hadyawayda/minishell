/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:05:41 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/23 10:55:45 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/wait.h>
#include <signal.h> // Include this header for signal handling
#include <unistd.h> // For write()

// Signal handler for SIGINT
// void handle_signal(int signal) {
//     if (signal == SIGINT) {
//         // Handle the interrupt signal (e.g., Ctrl+C)
//         write(1, "\nReceived SIGINT\n", 17);  // Optional message
//         // We can add any additional behavior here (e.g., ignore the signal)
//     }
// }

// Check if a command is a built-in command
int is_builtin(char *command) {
    return (ft_strcmp(command, "echo") == 0 || ft_strcmp(command, "cd") == 0 || ft_strcmp(command, "pwd") == 0 || ft_strcmp(command, "exit") == 0 || ft_strcmp(command, "env")  == 0 || ft_strcmp(command, "export") == 0) ;
}

// Execute built-in commands
int execute_builtin(char **args, char *envp[]) {
    if (!args[0]) {
        return (-1);  // Return error code if no command is provided
    }
    
    if (ft_strcmp(args[0], "echo") == 0) {
        process_echo(args);
        return (0);
    } 
    else if (ft_strcmp(args[0], "cd") == 0) {
        return (process_cd(args, envp));  // Handle `cd` command
    }
    else if(ft_strcmp(args[0], "pwd") == 0)
     { 
        return (process_pwd(args)); 
    } 
    else if (ft_strcmp(args[0], "exit") == 0)
   { return (process_exit(args, envp));
       }   
       else if (ft_strcmp(args[0], "env")  == 0)
       {   return (process_env(args, envp));
       }
       else if (ft_strcmp(args[0], "export")== 0)
      { return (process_export(args, envp));}
        return (-1); 
    
      // Not a built-in command
}

// Execute external commands
int execute_command(char **args) {
    pid_t pid;
    int status;

    if (!args[0]) {
        return (-1);  // Return error code if no command is provided
    }

    // Detect incorrect command names starting with "echo" but not exactly "echo"
    if (ft_strncmp(args[0], "echo", 4) == 0 && args[0][4] != '\0') {
        write(2, "bash: ", 6);  // Write the prefix for error message
        write(2, args[0], ft_strlen(args[0]));  // Write the command name
        write(2, ": command not found\n", 20);  // Write the error message
        return (-1);  // Return error code for incorrect command
    }

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            // If execvp fails
            write(2, "bash: ", 6);  // Write the prefix for error message
            write(2, args[0], ft_strlen(args[0]));  // Write the command name
            write(2, ": command not found\n", 20);  // Write the error message
            exit(127);  // Exit with 127 if command not found
        }
    } 
    else if (pid > 0) {
        // Parent process
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            return (WEXITSTATUS(status));  // Return the exit status of the child process
        }
    } 
    else {
        write(2, "fork error\n", 11);  // Error for failed fork
        return (-1);  // Return error code if fork fails
    }
    
    return (0);  // Return success if command executed successfully
}

// Start the shell loop
void start_shell(char *envp[]) {
    char *input;
    char **args;

    // Set up the signal handler for SIGINT (Ctrl+C)
    // signal(SIGINT, handle_signal);

    input = NULL;
    args = NULL;

    while (1) {
        input = readline("> ");  // Get user input
        if (!input) {  // Check for EOF (Ctrl+D)
            break;
        }

        if (ft_strlen(input) == 0) {  // Ignore empty input
            free(input);  // Free input
            continue;
        }

        add_history(input);  // Add input to history
        args = split_input(input);  // Parse input into args

        if (args) {
            if (args[0]) {
                if (ft_strcmp(args[0], "exit") == 0) {  // Handle `exit` command
                    free(input);
                    // Free each element of args using a while loop
                    int i = 0;
                    while (args[i]) {
                        free(args[i]);
                        i++;
                    }
                    free(args);
                    break;  // Exit the shell loop
                }

                // Handle built-in commands or external commands
                if (is_builtin(args[0])) {
                    execute_builtin(args, envp);  // Execute built-in command
                } else {
                    execute_command(args);  // Execute external command
                }
            }
        }

        // Free input here
        free(input);
        
        // Free each element of args using a while loop
        if (args) {
            int i = 0;
            while (args[i]) {
                free(args[i]);
                i++;
            }
            free(args);
        }
    }
}
