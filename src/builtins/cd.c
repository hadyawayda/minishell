/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:19:30 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/06 00:53:25 by nabbas           ###   ########.fr       */
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

int	process_cd(char **args, char **envp)
{
	char		cwd[PATH_MAX_LEN];
	char		*target_dir;
	struct stat	path_stat;

	(void)envp;
	target_dir = NULL;
	if (args[1] && args[2])
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		return (1);
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("bash: getcwd");
		return (1);
	}
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		target_dir = getenv("HOME");
		if (!target_dir)
		{
			write(2, "minishell: cd: HOME not set\n", 29);
			return (1);
		}
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		target_dir = getenv("OLDPWD");
		if (!target_dir)
		{
			write(2, "minishell: cd: OLDPWD not set\n", 31);
			return (1);
		}
		write(1, target_dir, ft_strlen(target_dir));
		write(1, "\n", 1);
	}
	else
	{
		target_dir = args[1];
	}
	if (stat(target_dir, &path_stat) != 0)
	{
		write(2, "minishell: cd: ", 16);
		write(2, target_dir, ft_strlen(target_dir));
		write(2, ": No such file or directory\n", 29);
		return (1);
	}
	if (!S_ISDIR(path_stat.st_mode))
	{
		write(2, "minishell: cd: ", 16);
		write(2, target_dir, ft_strlen(target_dir));
		write(2, ": Not a directory\n", 19);
		return (1);
	}
	if (chdir(target_dir) != 0)
	{
		perror("bash: cd");
		return (1);
	}
	// update_env_var("OLDPWD", cwd, envp);
	setenv("OLDPWD", cwd, 1);
	if (ft_strcmp(target_dir, "//") == 0)
	{
		// update_env_var("PWD", "//", envp);
		setenv("PWD", "//", 1);
	}
	else if (getcwd(cwd, sizeof(cwd)))
	{
		// update_env_var("PWD", cwd, envp);
		setenv("PWD", cwd, 1);
	}
	return (0);
}
