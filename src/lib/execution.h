/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:27:48 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/04 23:47:37 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "core.h"

char	**build_argv(t_ast *node);
char	**build_envp(t_env *env);
char	*find_executable(t_shell *sh, char *cmd);

int		execute_and(t_shell *shell, t_ast *node);
int		execute_or(t_shell *shell, t_ast *node);
int		execute_cmd(t_shell *shell, t_ast *node);
int		execute_pipe(t_shell *shell, t_ast *node);
int		execute_ast(t_shell *shell, t_ast *node);
int		launch_external(t_shell *sh, char **argv, t_redir *redirs);
int		builtin_env(t_shell *sh, char **argv);
int		builtin_export(t_shell *sh, char **argv);
int		builtin_unset(t_shell *sh, char **argv);

void	free_argv(char **argv);
void	apply_redirections(t_redir *redirs);

#endif
