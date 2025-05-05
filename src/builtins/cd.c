/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:19:30 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/05 15:14:00 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"   
#include "builtins.h"

#define PATH_MAX_LEN 1024

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:19:30 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/05 15:00:00 by nabbas           ###   ########.fr       */
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

static int	get_target(char **args, char **target,
				 int *dash, int *double_slash)
{
	char	*src;

	*dash = 0;
	*double_slash = (args[1] && ft_strcmp(args[1], "//") == 0);
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
	return (*target == NULL);
}

static int	change_directory(char *target)
{
	struct stat	st;

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
	free(target);
	return (0);
}

static void	update_pwd(int dash, int double_slash)
{
	char	cwd[PATH_MAX_LEN];

	if (dash && getcwd(cwd, PATH_MAX_LEN))
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
	}
	setenv("OLDPWD", getenv("PWD"), 1);
	if (double_slash)
		setenv("PWD", "//", 1);
	else if (getcwd(cwd, PATH_MAX_LEN))
		setenv("PWD", cwd, 1);
}

int	process_cd(char **args, char **envp)
{
	char	*target;
	int		dash;
	int		dbl_sl;

	(void)envp;
	if (args[1] && args[2])
		return (print_too_many());
	if (args[1] && ft_strchr(args[1], '*'))
		return (print_too_many());
	if (get_target(args, &target, &dash, &dbl_sl))
		return (1);
	if (change_directory(target))
		return (1);
	update_pwd(dash, dbl_sl);
	return (0);
}
