/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 00:00:58 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/17 00:56:04 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "minishell.h"
# include "execution.h"
# include "lexer.h"
# include "parser.h"

char	*get_env_value(t_env *env, char *key);

int		env_list_contains(t_env *env, char *key);
int		is_valid_varname(char *var);
int		add_or_update_env_variable(t_env **env, char *key, char *value);
int		add_env_variable(t_env **env, char *key, char *value);

void	free_env(t_env *env);
void	minishell(char **env);
void	shell_loop(t_shell *shell);
void	free_shell(t_shell *shell);
void	list_export(t_env *env);
void	sort_env_list(t_env **env);
void	unset_env_variable(t_env **env, char *key);
void	update_env_variable(t_env **env, char *key, char *value);

void	setup_signal_handlers(void);
void	non_interactive_minishell(char **av, char **envp);
void	setup_heredoc_signals(struct sigaction *old_int,
			struct sigaction *old_quit);
void	restore_heredoc_signals(struct sigaction *old_int,
			struct sigaction *old_quit);

t_env	*clone_env(char **envp);
t_env	*create_env_node(char *key, char *value);
t_env	*parse_env_entry(char *env_entry);
t_env	*clone_env_list(t_env *env);

t_shell	*init_shell(char **envp);

#endif