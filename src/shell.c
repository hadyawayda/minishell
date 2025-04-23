/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:05:41 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/23 14:06:03 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

// Check if a command is a built-in command
int is_builtin(char *command) {
    return (ft_strcmp(command, "echo") == 0
         || ft_strcmp(command, "cd")   == 0
         || ft_strcmp(command, "pwd")  == 0
         || ft_strcmp(command, "exit") == 0
         || ft_strcmp(command, "env")  == 0
         || ft_strcmp(command, "export")== 0);
}

// Execute built-in commands
int execute_builtin(char **args, char *envp[]) {
    if (!args[0])
        return (-1);

    if (ft_strcmp(args[0], "echo") == 0)
        return (process_echo(args), 0);
    if (ft_strcmp(args[0], "cd") == 0)
        return (process_cd(args, envp));
    if (ft_strcmp(args[0], "pwd") == 0)
        return (process_pwd(args));
    if (ft_strcmp(args[0], "exit") == 0)
        return (process_exit(args, envp));
    if (ft_strcmp(args[0], "env") == 0)
        return (process_env(args, envp));
    if (ft_strcmp(args[0], "export") == 0)
        return (process_export(args, envp));

    return (-1);
}

// Execute external commands
int execute_command(char **args) {
    pid_t pid;
    int   status;

    if (!args[0])
        return (-1);

    // Detect "echoX" errors
    if (ft_strncmp(args[0], "echo", 4) == 0 && args[0][4] != '\0') {
        write(2, "bash: ", 6);
        write(2, args[0], ft_strlen(args[0]));
        write(2, ": command not found\n", 20);
        return (-1);
    }

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            write(2, "bash: ", 6);
            write(2, args[0], ft_strlen(args[0]));
            write(2, ": command not found\n", 20);
            exit(127);
        }
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
    } else {
        write(2, "fork error\n", 11);
        return (-1);
    }
    return (0);
}

// Start the shell loop
void start_shell(char *envp[]) {
    char *input;
    char **args;

    while (1) {
        input = readline("> ");
        if (!input)
            break;

        if (ft_strlen(input) == 0) {
            free(input);
            continue;
        }

        add_history(input);
        args = split_input(input);

        if (args && args[0]) {
            if (is_builtin(args[0]))
                execute_builtin(args, envp);
            else
                execute_command(args);
        }

        free(input);
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
