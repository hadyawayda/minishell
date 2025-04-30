/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:28:01 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/30 12:18:48 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

/*
** convert_to_ll: parse optional +/- then digits with overflow check
*/
static int	convert_to_ll(const char *s, long long *out)
{
	int		 i;
	int		 sign;
	unsigned long long	 num;
	int		 d;

	i = 0;
	sign = 1;
	if ((s[i] == '+' || s[i] == '-')
		&& s[i + 1] != '\0')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (s[i] == '\0')
		return (0);
	num = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		d = s[i++] - '0';
		if (sign == 1
			&& num > (LLONG_MAX - d) / 10)
			return (0);
		if (sign == -1
			&& num > ((unsigned long long)LLONG_MAX + 1ULL - d) / 10)
			return (0);
		num = num * 10 + d;
	}
	*out = sign * num;
	return (1);
}

/*
** process_exit: print exit and handle numeric argument
*/
int	process_exit(char **args, char **envp)
{
	int			count;
	long long	val;

	(void)envp;
	ft_putendl_fd("exit", 1);
	count = 0;
	while (args[count])
		count++;
	if (count == 1)
		exit(0);
	if (!convert_to_ll(args[1], &val))
	{
		write(2, "bash: exit: ", 12);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": numeric argument required\n", 29);
		return (1);
	}
	if (count > 2)
	{
		write(2, "bash: exit: too many arguments\n", 31);
		return (1);
	}
	exit((unsigned char)val);
	return (0);
}
