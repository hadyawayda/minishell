/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:51:45 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/07 15:29:47 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "builtins.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

#define PATH_MAX_LEN 1024

static int	get_target(char **args, char **target, int *dash, int *dbl_sl)
{
	char	*home;

	*dbl_sl = (args[1] && ft_strcmp(args[1], "//") == 0);
	if (!args[1] || !ft_strcmp(args[1], "~") || !ft_strcmp(args[1], "--"))
		return (set_target_from_env(target, "HOME", NULL));
	if (!ft_strcmp(args[1], "-"))
		return (set_target_from_env(target, "OLDPWD", dash));
	if (!ft_strncmp(args[1], "~/", 2) || !ft_strcmp(args[1], "~/"))
	{
		home = getenv("HOME");
		if (!home)
			return (cd_env_error("HOME"));
		*target = ft_strjoin(home, args[1] + 1);
		return (*target == NULL);
	}
	*target = ft_strdup(args[1]);
	return (*target == NULL);
}

/* ---------------- perform chdir & checks -------------------- */
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

/* ------------- compute the new PWD value -------------------- */
static void	set_pwd_value(const char *prev_pwd, int dbl_sl)
{
	char	cwd[PATH_MAX_LEN];
	char	tmp[PATH_MAX_LEN + 3];

	if (dbl_sl)
	{
		setenv("PWD", "//", 1);
		return ;
	}
	if (!getcwd(cwd, PATH_MAX_LEN))
	{
		print_getcwd_error("chdir");
		return ;
	}
	if (prev_pwd && prev_pwd[0] == '/' && prev_pwd[1] == '/')
	{
		ft_strlcpy(tmp, "//", sizeof(tmp));
		if (cwd[0] == '/' && cwd[1] == '/')
			ft_strlcat(tmp, cwd + 2, sizeof(tmp));
		else
			ft_strlcat(tmp, cwd + 1, sizeof(tmp));
		setenv("PWD", tmp, 1);
	}
	else
		setenv("PWD", cwd, 1);
}

/* -------------- update PWD / OLDPWD + echo for cd - -------- */
static void	update_pwd(const char *prev_pwd, int dash, int dbl_sl)
{
	char	cwd[PATH_MAX_LEN];

	if (dash)
	{
		if (!getcwd(cwd, PATH_MAX_LEN))
			print_getcwd_error("chdir");
		else
		{
			write(1, cwd, ft_strlen(cwd));
			write(1, "\n", 1);
		}
	}
	if (prev_pwd)
		setenv("OLDPWD", prev_pwd, 1);
	else
		setenv("OLDPWD", "", 1);
	set_pwd_value(prev_pwd, dbl_sl);
}

/* ----------------------------- builtin --------------------- */
int	process_cd(char **args, char **envp)
{
	char	*target;
	char	*prev_pwd;
	int		dash;
	int		dbl_sl;

	(void)envp;
	if (args[1] && args[2])
		return (write(2, "minishell: cd: too many arguments\n", 35), 1);
	if (args[1] && ft_strchr(args[1], '*'))
		return (write(2, "minishell: cd: too many arguments\n", 35), 1);
	prev_pwd = getenv("PWD");
	dash = 0;
	if (get_target(args, &target, &dash, &dbl_sl))
		return (1);
	if (change_directory(target))
		return (1);
	update_pwd(prev_pwd, dash, dbl_sl);
	return (0);
}
