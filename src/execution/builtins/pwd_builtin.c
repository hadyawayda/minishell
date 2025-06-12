/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:09:20 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/13 00:43:21 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

#define PATH_MAX_LEN 1024

static int	invalid_opt(const char *s)
{
	if (!s || s[0] != '-' || !s[1])
		return (0);
	if (s[1] == '-')
		write(2, "pwd: --: invalid option\n", 24);
	else
	{
		write(2, "pwd: ", 5);
		write(2, s, ft_strlen(s));
		write(2, ": invalid option\n", 18);
	}
	return (1);
}

int	builtin_pwd(char **args)
{
	char	buf[PATH_MAX_LEN];
	char	*pwd;

	if (invalid_opt(args[1]))
		return (1);
	if (!getcwd(buf, PATH_MAX_LEN))
		return (print_getcwd_error("pwd"));
	pwd = getenv("PWD");
	if (pwd && pwd[0] == '/' && pwd[1] == '/')
		write(1, pwd, ft_strlen(pwd));
	else
		write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	return (0);
}
