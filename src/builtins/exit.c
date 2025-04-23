/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:28:01 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/23 10:02:03 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

static int	convert_to_ll(const char *str, long long *result)
{
	int			 i = 0;
	int			 sign = 1;
	long long	 num = 0;
	int			 d;

	/* single optional sign */
	if ((str[i] == '+' || str[i] == '-') &&
		!(str[i + 1] == '+' || str[i + 1] == '-'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	/* need at least one digit */
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		d = str[i++] - '0';
		if (sign == 1)
		{
			if (num > (LLONG_MAX - d) / 10)
				return (0);
		}
		else
		{
			if ((unsigned long long)num >
				(((unsigned long long)LLONG_MAX + 1ULL) - (unsigned long long)d) / 10)
				return (0);
		}
		num = num * 10 + d;
	}
	*result = sign * num;
	return (1);
}
int	process_exit(char **args, char **envp)
{
	long long	num;
	int			cnt = 0;

	(void)envp;
	ft_putendl_fd("exit", 1);
	while (args[cnt])
		cnt++;
	/* no args */
	if (cnt == 1)
		exit(0);
	/* invalid number? */
	if (!convert_to_ll(args[1], &num))
	{
		write(2, "bash: exit: ", 12);
		write(2, args[1],  ft_strlen(args[1]));
		write(2, ": numeric argument required\n",
			  ft_strlen(": numeric argument required\n"));
		exit(2);
	}
	/* too many args */
	if (cnt > 2)
	{
		write(2, "bash: exit: too many arguments\n",
			  ft_strlen("bash: exit: too many arguments\n"));
		return (1);
	}
	/* single valid number */
	exit((unsigned char)num);
}