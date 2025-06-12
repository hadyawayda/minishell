/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:28:01 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/13 00:26:56 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	accumulate_number(const char *s, int *i, unsigned long long *num)
{
	unsigned long long	d;

	while (ft_isdigit(s[*i]))
	{
		d = (unsigned long long)(s[(*i)++] - '0');
		if (*num > (ULLONG_MAX - d) / 10ULL)
			return (0);
		*num = *num * 10ULL + d;
	}
	return (1);
}

static int	convert_to_ll(const char *s, long long *out)
{
	int					i;
	int					sign;
	unsigned long long	num;

	i = 0;
	sign = 1;
	num = 0;
	if ((s[i] == '+' || s[i] == '-') && s[i + 1])
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (!s[i] || !ft_isdigit(s[i]))
		return (0);
	if (!accumulate_number(s, &i, &num))
		return (0);
	*out = (long long)(sign * (long long)num);
	return (1);
}

static int	print_exit_error(char *arg, int code)
{
	if (code == 1)
	{
		write(2, "bash: exit: ", 12);
		write(2, arg, ft_strlen(arg));
		write(2, ": numeric argument required\n", 29);
	}
	else
		write(2, "bash: exit: too many arguments\n", 31);
	return (1);
}

int	builtin_exit(char **args)
{
	int			count;
	long long	val;

	count = 0;
	while (args[count])
		count++;
	if (count == 1)
		exit(0);
	if (!convert_to_ll(args[1], &val))
		return (print_exit_error(args[1], 1));
	if (count > 2)
		return (print_exit_error(args[1], 2));
	exit((unsigned char)val);
	return (0);
}
