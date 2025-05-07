/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:09:20 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/07 12:09:22 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdlib.h>

#define PATH_MAX_LEN 1024

static int	invalid_opt(const char *s)
{
	if (!s || s[0] != '-' || !s[1])
		return (0);
	if (s[1] == '-')
		write(2, "bash: pwd: --: invalid option\n", 31);
	else
	{
		write(2, "bash: pwd: ", 12);
		write(2, s, ft_strlen(s));
		write(2, ": invalid option\n", 18);
	}
	return (1);
}

int	process_pwd(char **args)
{
	char	*pwd;
	char	buf[PATH_MAX_LEN];

	if (invalid_opt(args[1]))
		return (1);
	pwd = getenv("PWD");
	if (pwd && *pwd)
		return (write(1, pwd, ft_strlen(pwd)), write(1, "\n", 1), 0);
	if (!getcwd(buf, PATH_MAX_LEN))
		return (perror("bash: pwd"), 1);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	return (0);
}
