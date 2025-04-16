/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:25:53 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/16 11:56:48 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <errno.h> // for errno
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // for stat()
#include <unistd.h>
#include <limits.h>
#define PATH_MAX 4096

int process_pwd(char **args)
{ 
    char cwd[PATH_MAX];
    if (args[1] && args[1][0] == '-' && args[1][1] != '\0')
{
    if (args[1][1] == '-')
    {
        write(2, "bash: pwd: --: invalid option\n", 31);
    }
    else
    {
        write(2, "bash: pwd: ", 12);
        write(2, args[1], ft_strlen(args[1]));
        write(2, ": invalid option\n", 18);
    }
    return (1);
}
if (!getcwd(cwd, sizeof(cwd)))
{
    perror("bash: pwd");
    return (1);
}
write(1, cwd, ft_strlen(cwd));
write(1, "\n", 1);
return (0);

}

    