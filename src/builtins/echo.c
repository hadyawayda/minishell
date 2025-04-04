/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:05:30 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/02 13:15:09 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void process_echo(char **args) {
    int i = 1;  
    bool newline_flag = true;  

    // Handle multiple `-n` flags at the start
    while (args[i] && args[i][0] == '-' && args[i][1] == 'n') {
        int j = 1;
        while (args[i][j] == 'n') {
            j++;
        }
        if (args[i][j] != '\0') {
            break;  
        }
        newline_flag = false;  
        i++;  
    }

    bool first_word = true;

    // Print remaining arguments
    while (args[i]) {
        // Special case: Handle `echo \n hola`
        if (strcmp(args[i], "\\n") == 0) {
            if (!first_word) {
                printf(" ");  // Ensure space before 'n'
            }
            printf("n");
        } else {
            if (!first_word) {
                printf(" ");  // Ensure space between words
            }
            printf("%s", args[i]);
        }
        first_word = false;
        i++;
    }

    // Print newline unless `-n` flag was set
    if (newline_flag) {
        printf("\n");
    }
}
