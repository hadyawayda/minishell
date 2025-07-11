/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:27:48 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/20 21:29:05 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define PATH_MAX_LEN 1024

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
int		builtin_env(t_shell *sh);
int		builtin_export(t_shell *sh, char **argv);
int		builtin_unset(t_shell *sh, char **argv);
int		process_cd(char **args, char **envp);
int		process_pwd(char **args);
int		process_exit(char **args, char **envp);
int		process_env(char **args, char **envp);
int		process_export(char **args, char **envp);
int		cmp_key(const char *a, const char *b);
int		cd_env_error(char *var);
int		set_target_from_env(char **target, char *var, int *dash, t_env *env);
int		print_getcwd_error(char *cmd);
int		builtin_cd(char **args, t_env *env);
int		builtin_exit(char **args);
int		builtin_pwd(char **args);
int		builtin_echo(t_ast *node, char **args);
int		handle_child_builtin(t_shell *shell, t_ast *node, char **argv);

void	free_argv(char **argv);
void	apply_redirections(t_redir *redirs);
void	process_echo(char **args);
void	exec_error_and_exit(char *exec_path, char **argv, char **envp);
void	check_directory_and_exit(char *exec_path, char **argv, char **envp);

pid_t	get_pid(void);

#endif
