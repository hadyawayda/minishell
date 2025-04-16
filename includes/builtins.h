/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:05:08 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/16 13:06:06 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

void process_echo(char **args);
int process_cd(char **args, char *envp[]); // Declare cd function
int process_pwd(char **args);


#endif
