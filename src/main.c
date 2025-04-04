/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:06:00 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/02 21:29:57 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[]) {
    if (argc > 1 && strcmp(argv[1], "-c") == 0 && argc > 2) {
        char **args = split_input(argv[2]);

        if (args && args[0]) {
            if (is_builtin(args[0])) {
                execute_builtin(args, envp);  // Pass envp
            } else {
                execute_command(args);
            }
        }
        free(args);
    } else {
        start_shell(envp);  // Pass envp to shell
    }
    return 0;
}

