/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:28:01 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/23 14:01:15 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:30:00 by assistant         #+#    #+#             */
/*   Updated: 2025/04/23 19:30:00 by assistant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

/*
** convert_to_ll:
**   Parse an optional single '+' or '-' then digits.
**   Return 1 on success (store in *out), 0 on any error (nondigit or overflow).
*/
static int convert_to_ll(const char *s, long long *out)
{
    int          sign = 1;
    long long    num  = 0;
    int          i    = 0;
    int          d;

    if ((s[i] == '+' || s[i] == '-') &&
        !(s[i+1] == '+' || s[i+1] == '-'))
        sign = (s[i++] == '-') ? -1 : 1;

    if (!s[i]) /* no digits */
        return (0);

    while (s[i])
    {
        if (!ft_isdigit(s[i]))
            return (0);
        d = s[i++] - '0';
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
    *out = sign * num;
    return (1);
}

/*
** process_exit:
**   – Always prints "exit\n"
**   – No args: exit(0)
**   – One arg:
**       • non-numeric → error, return 1
**       • numeric     → exit(code % 256)
**   – >1 arg:
**       • first non-numeric → error, return 1
**       • first numeric     → "too many arguments", return 1
*/
int process_exit(char **args, char **envp)
{
    int          count = 0;
    long long    val;

    (void)envp;
    ft_putendl_fd("exit", 1);
    while (args[count])
        count++;

    /* case: no argument */
    if (count == 1)
        exit(0);

    /* try parsing first argument */
    if (!convert_to_ll(args[1], &val))
    {
        write(2, "bash: exit: ", 12);
        write(2, args[1],   ft_strlen(args[1]));
        write(2, ": numeric argument required\n", 29);
        return (1);
    }

    /* too many args? */
    if (count > 2)
    {
        write(2, "bash: exit: too many arguments\n", 31);
        return (1);
    }

    /* one valid number */
    exit((unsigned char)val);
}
