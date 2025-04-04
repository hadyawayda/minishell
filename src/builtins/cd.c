/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:19:30 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/04 19:28:28 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>  // for stat()
#include <errno.h>     // for errno
#define PATH_MAX_LEN 1024

// Function to update environment variables (PWD and OLDPWD)
void update_env_var(char *key, char *value, char **envp) {
    int i = 0;
    size_t key_len = strlen(key);

    while (envp[i]) {
        if (strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=') {
            snprintf(envp[i], 1024, "%s=%s", key, value);
            return;
        }
        i++;
    }
}


int process_cd(char **args) {
    char cwd[PATH_MAX_LEN];
    char *target_dir = NULL;
    struct stat path_stat;

    // Handle too many arguments
    if (args[1] && args[2]) {
        fprintf(stderr, "bash: cd: too many arguments\n");
        return 1;
    }

    // Save current directory
    if (!getcwd(cwd, sizeof(cwd))) {
        perror("bash: getcwd");
        return 1;
    }

    // Determine target directory
    if (!args[1] || strcmp(args[1], "~") == 0) {
        target_dir = getenv("HOME");
        if (!target_dir) {
            fprintf(stderr, "bash: cd: HOME not set\n");
            return 1;
        }
    } else if (strcmp(args[1], "-") == 0) {
        target_dir = getenv("OLDPWD");
        if (!target_dir) {
            fprintf(stderr, "bash: cd: OLDPWD not set\n");
            return 1;
        }
        printf("%s\n", target_dir); // Show old path
    } else {
        target_dir = args[1];
    }

    // Check path validity
    if (stat(target_dir, &path_stat) != 0) {
        fprintf(stderr, "bash: cd: %s: No such file or directory\n", target_dir);
        return 1;
    }
    if (!S_ISDIR(path_stat.st_mode)) {
        fprintf(stderr, "bash: cd: %s: Not a directory\n", target_dir);
        return 1;
    }

    // Try to change directory
    if (chdir(target_dir) != 0) {
        perror("bash: cd");
        return 1;
    }

    // Set OLDPWD to previous directory
    setenv("OLDPWD", cwd, 1);

    // Preserve leading "//" (Bash behavior)
    if (strcmp(target_dir, "//") == 0) {
        setenv("PWD", "//", 1);
    } else if (getcwd(cwd, sizeof(cwd))) {
        setenv("PWD", cwd, 1);
    }

    return 0;
}
