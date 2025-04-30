/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:19:30 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/30 11:59:10 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#define PATH_MAX_LEN 1024

static int	print_too_many(void)
{
	write(2, "minishell: cd: too many arguments\n", 35);
	return (1);
}

static int	setup_target(char **args, char **target, int *dash)
{
	char	*src;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		src = getenv("HOME");
	else if (ft_strcmp(args[1], "-") == 0)
	{
		src = getenv("OLDPWD");
		*dash = 1;
	}
	else
		src = args[1];
	if (!src)
	{
		write(2, "minishell: cd: HOME not set\n", 29);
		return (1);
	}
	*target = ft_strdup(src);
	if (!*target)
		return (1);
	return (0);
}

int	process_cd(char **args, char **envp)
{
	char		cwd[PATH_MAX_LEN];
	char		*target;
	struct stat	st;
	int			dash;

	(void)envp;
	dash = 0;
	if (args[1] && args[2])
		return (print_too_many());
	if (args[1] && ft_strchr(args[1], '*'))
		return (print_too_many());
	if (!getcwd(cwd, PATH_MAX_LEN))
		return (perror("minishell: getcwd"), 1);
	if (setup_target(args, &target, &dash))
		return (1);
	if (stat(target, &st) != 0 || !S_ISDIR(st.st_mode))
	{
		write(2, "minishell: cd: ", 15);
		write(2, target, ft_strlen(target));
		write(2, ": No such directory\n", 21);
		free(target);
		return (1);
	}
	if (chdir(target) != 0)
	{
		perror("minishell: cd");
		free(target);
		return (1);
	}
	if (dash)
	{
		if (getcwd(cwd, PATH_MAX_LEN))
			write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
	}
	setenv("OLDPWD", getenv("PWD"), 1);
	getcwd(cwd, PATH_MAX_LEN);
	setenv("PWD", cwd, 1);
	free(target);
	return (0);
}
