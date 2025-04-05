/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:09:26 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/05 23:47:01 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>  // for fork() and execvp()


char **split_input(const char *input) {
    char **args = malloc(256 * sizeof(char *));
    if (!args) return NULL;

    int i = 0;
    const char *start = input;
    while (*start) {
        while (*start == ' ' || *start == '\t' || *start == '\n')
            start++;  // Skip whitespace

        if (*start == '\0')
            break;

        const char *end = start;
        while (*end && *end != ' ' && *end != '\t' && *end != '\n')
            end++;

        size_t len = end - start;
        args[i] = malloc(len + 1);
        if (!args[i]) return NULL;
        ft_strncpy(args[i], start, len);
        args[i][len] = '\0';
        i++;

        start = end;
    }
    args[i] = NULL;
    return args;
}

