/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:04:57 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/04 20:15:16 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/includes/libft.h"


// Function Prototypes
void start_shell(char *envp[]); 
int is_builtin(char *command);
int execute_builtin(char **args, char *envp[]);
int execute_command(char **args);
char **split_input(char *input);

#endif
