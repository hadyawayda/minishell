/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:51:45 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/12 00:39:31 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/execution.h"

#define PATH_MAX_LEN 1024

static int	get_target(char **args, t_cd_ctx *ctx, t_env *env)
{
	char	*home;

	ctx->dbl_sl = (args[1] && ft_strcmp(args[1], "//") == 0);
	if (!args[1] || !ft_strcmp(args[1], "~") || !ft_strcmp(args[1], "--"))
		return (set_target_from_env(&ctx->target, "HOME", NULL, env));
	if (!ft_strcmp(args[1], "-"))
		return (set_target_from_env(&ctx->target, "OLDPWD", &ctx->dash, env));
	if (!ft_strncmp(args[1], "~/", 2) || !ft_strcmp(args[1], "~/"))
	{
		home = get_env_value(env, "HOME");
		if (!home || *home == '\0')
			return (cd_env_error("HOME"));
		ctx->target = ft_strjoin(home, args[1] + 1);
		return (ctx->target == NULL);
	}
	ctx->target = ft_strdup(args[1]);
	return (ctx->target == NULL);
}

/* ---------------- perform chdir & checks -------------------- */
static int	change_directory(char *target)
{
	struct stat	st;

	// forbidden function S_ISDIR
	if (stat(target, &st) != 0 || !S_ISDIR(st.st_mode))
	{
		printf("%s", "minishell: cd: ");
		printf("%s", target);
		printf("%s", ": No such directory\n");
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
static void	set_pwd_value(t_env *env, t_cd_ctx *ctx)
{
	char	cwd[PATH_MAX_LEN];
	char	tmp[PATH_MAX_LEN + 3];

	if (ctx->dbl_sl)
	{
		update_env_variable(&env, "PWD", "//");
		return ;
	}
	if (!getcwd(cwd, PATH_MAX_LEN))
	{
		print_getcwd_error("chdir");
		return ;
	}
	if (ctx->prev_pwd && ctx->prev_pwd[0] == '/' && ctx->prev_pwd[1] == '/')
	{
		ft_strlcpy(tmp, "//", sizeof(tmp));
		if (cwd[0] == '/' && cwd[1] == '/')
			ft_strlcat(tmp, cwd + 2, sizeof(tmp));
		else
			ft_strlcat(tmp, cwd + 1, sizeof(tmp));
		update_env_variable(&env, "PWD", tmp);
	}
	else
		update_env_variable(&env, "PWD", cwd);
}

/* -------------- update PWD / OLDPWD + echo for cd - -------- */
static void	update_pwd(t_env *env, t_cd_ctx *ctx)
{
	char	cwd[PATH_MAX_LEN];

	if (ctx->dash)
	{
		if (!getcwd(cwd, PATH_MAX_LEN))
			print_getcwd_error("chdir");
		else
		{
			printf("%s", cwd);
			printf("%s", "\n");
		}
	}
	if (ctx->prev_pwd)
		update_env_variable(&env, "OLDPWD", ctx->prev_pwd);
	else
		update_env_variable(&env, "OLDPWD", "");
	set_pwd_value(env, ctx);
}

/* ----------------------------- builtin --------------------- */
int	builtin_cd(char **args, t_env *env)
{
	t_cd_ctx	ctx;

	if (args[1] && args[2])
		return (printf("%s", "minishell: cd: too many arguments\n"), 1);
	if (args[1] && ft_strchr(args[1], '*'))
		return (printf("%s", "minishell: cd: too many arguments\n"), 1);
	ctx.prev_pwd = get_env_value(env, "PWD");
	ctx.dash = 0;
	ctx.dbl_sl = 0;
	if (get_target(args, &ctx, env))
		return (1);
	if (change_directory(ctx.target))
		return (1);
	update_pwd(env, &ctx);
	return (0);
}
