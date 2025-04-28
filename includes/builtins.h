/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:05:08 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/28 12:31:11 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	process_echo(char **args);
int		process_cd(char **args, char **envp);
int		process_pwd(char **args);
int		process_exit(char **args, char **envp);
int		process_env(char **args, char **envp);
int		process_export(char **args, char **envp);

#endif
