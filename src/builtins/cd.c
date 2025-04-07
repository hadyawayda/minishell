/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:19:30 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/07 15:49:39 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <errno.h> // for errno
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // for stat()
#include <unistd.h>
#define PATH_MAX_LEN 1024

// ** This function belongs to the export logic **
// SAFELY updates or appends a key=value to envp
// void update_env_var(char *key, char *value, char **envp) {
//     int i = 0;
//     size_t key_len = ft_strlen(key);
//     size_t val_len = ft_strlen(value);
//     char *new_entry = malloc(key_len + val_len + 2); // key=value\0

//     if (!new_entry) {
//         write(2, "Memory allocation failed\n", 26);
//         return ;
//     }

//     ft_strcpy(new_entry, key);
//     new_entry[key_len] = '=';
//     ft_strcpy(new_entry + key_len + 1, value);

//     // Search for existing key
//     while (envp[i]) {
//         if (ft_strncmp(envp[i], key, key_len) == 0
// && envp[i][key_len] == '=')
// {
//             // Don't free envp[i] — we didn’t allocate it
//             envp[i] = new_entry;
//             return ;
//         }
//         i++;
//     }

//     // Append new entry if not found
//     envp[i] = new_entry;
//     envp[i + 1] = NULL;
// }
int process_cd(char **args, char **envp)
{
    char cwd[PATH_MAX_LEN];
    char *target_dir = NULL;
    struct stat path_stat;
    int was_allocated = 0;
    int is_dash = 0; // New flag to track if "cd -" was used

    (void)envp;

    // Case: Too many arguments
    if (args[1] && args[2])
    {
        write(2, "minishell: cd: too many arguments\n", 35);
        return (1);
    }

    // Case: `cd *` - Wildcard check for too many arguments
    if (args[1] && ft_strchr(args[1], '*') != NULL)
    {
        write(2, "minishell: cd: too many arguments\n", 35);
        return (1);
    }

    // Get current working directory (OLDPWD)
    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("minishell: getcwd");
        return (1);
    }

    // Case: cd or cd ~
    // Case: cd, cd ~, or cd --
	if (!args[1] || ft_strcmp(args[1], "~") == 0 || ft_strcmp(args[1], "--") == 0)
    {
        target_dir = getenv("HOME");
        if (!target_dir)
        {
            write(2, "minishell: cd: HOME not set\n", 29);
            return (1);
        }
    }
    // Case: cd -
    else if (ft_strcmp(args[1], "-") == 0)
    {
        target_dir = getenv("OLDPWD");
        if (!target_dir)
        {
            write(2, "minishell: cd: OLDPWD not set\n", 31);
            return (1);
        }
        is_dash = 1; // Set flag for cd -
    }
    // Case: cd ~/ or cd ~anything
    else if (args[1][0] == '~')
    {
        char *home = getenv("HOME");
        if (!home)
        {
            write(2, "minishell: cd: HOME not set\n", 29);
            return (1);
        }
        target_dir = ft_strjoin(home, args[1] + 1); // skip the ~
        if (!target_dir)
            return (1);
        was_allocated = 1;
    }
    // Case: normal path
    else
    {
        target_dir = ft_strdup(args[1]);
        if (!target_dir)
            return (1);
        was_allocated = 1;
    }

    // Validate path
    if (stat(target_dir, &path_stat) != 0)
    {
        write(2, "minishell: cd: ", 16);
        write(2, target_dir, ft_strlen(target_dir));
        write(2, ": No such file or directory\n", 29);
        if (was_allocated)
            free(target_dir);
        return (1);
    }
    if (!S_ISDIR(path_stat.st_mode))
    {
        write(2, "minishell: cd: ", 16);
        write(2, target_dir, ft_strlen(target_dir));
        write(2, ": Not a directory\n", 19);
        if (was_allocated)
            free(target_dir);
        return (1);
    }

    // Change directory
    if (chdir(target_dir) != 0)
    {
        perror("minishell: cd");
        if (was_allocated)
            free(target_dir);
        return (1);
    }

    // Print new cwd if "cd -" was used
    if (is_dash && getcwd(cwd, sizeof(cwd)))
    {
        write(1, cwd, ft_strlen(cwd));
        write(1, "\n", 1);
    }

    // Update OLDPWD
    setenv("OLDPWD", cwd, 1);

    // Special handling for cd // (preserve double slash)
    if (ft_strcmp(target_dir, "//") == 0)
        setenv("PWD", "//", 1);
    else if (getcwd(cwd, sizeof(cwd)))
        setenv("PWD", cwd, 1);

    if (was_allocated)
        free(target_dir);

    return (0);
}
