/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:09:26 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/04 20:47:22 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>  // for fork() and execvp()


// Function to split input string into arguments
char **split_input(char *input) {
    char **args = malloc(256 * sizeof(char *));
    if (!args) {
        perror("malloc");
        return NULL;
    }

    int i = 0;
    char *token = ft_strtok(input, " \t\n");
    while (token != NULL) {
        args[i++] = ft_strdup(token);
        token = ft_strtok(NULL, " \t\n");
    }
    args[i] = NULL;
    return args;
}

