/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:09:20 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/20 21:29:11 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	invalid_opt(char *s)
{
	if (!s || s[0] != '-' || !s[1])
		return (0);
	if (s[1] == '-')
		ft_putstr_fd("pwd: --: invalid option\n", 2);
	else
	{
		ft_putstr_fd("pwd: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": invalid option\n", 2);
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
		ft_putstr_fd(pwd, 1);
	else
		ft_putstr_fd(buf, 1);
	write(1, "\n", 1);
	return (0);
}
