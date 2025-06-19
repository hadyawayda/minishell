/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:28:01 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/19 20:31:29 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/* initialize index, sign, and overflow limit */
static int	init_conv(const char *s, int *i, int *sign,
		unsigned long long *limit)
{
	*i = 0;
	*sign = 1;
	if ((s[*i] == '+' || s[*i] == '-') && s[*i + 1] != '\0')
	{
		if (s[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	if (*sign > 0)
		*limit = LLONG_MAX;
	else
		*limit = (unsigned long long)LLONG_MAX + 1ULL;
	return (1);
}

/* accumulate digits into *val without exceeding limit */
static int	accumulate_with_limit(const char *s, int *i,
		unsigned long long *val, unsigned long long limit)
{
	unsigned long long	d;

	while (ft_isdigit(s[*i]))
	{
		d = (unsigned long long)(s[(*i)] - '0');
		if (*val > limit / 10ULL || (*val == limit / 10ULL && d > limit
				% 10ULL))
			return (0);
		*val = *val * 10ULL + d;
		(*i)++;
	}
	return (1);
}

/* convert s to signed long long in *out; returns 1 on valid range */
static int	convert_to_ll(const char *s, long long *out)
{
	int					i;
	int					sign;
	unsigned long long	val;
	unsigned long long	limit;

	init_conv(s, &i, &sign, &limit);
	if (!ft_isdigit(s[i]))
		return (0);
	val = 0ULL;
	if (!accumulate_with_limit(s, &i, &val, limit))
		return (0);
	if (s[i] != '\0')
		return (0);
	if (sign > 0)
		*out = (long long)val;
	else
		*out = -(long long)val;
	return (1);
}

static int	print_exit_error(char *arg, int code)
{
	if (code == 1)
	{
		write(2, "bash: exit: ", 12);
		write(2, arg, ft_strlen(arg));
		write(2, ": numeric argument required\n", 29);
		return (2);
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
