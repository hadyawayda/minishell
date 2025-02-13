/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 00:00:58 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/13 02:48:17 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "../../includes/minishell.h"
# include "../parser/parser.h"
# include <stdlib.h>
# include <string.h>

char				*expand_variables(char *input, t_env *env);

void				free_env(t_env *env);
void				minishell(char **env);
void				shell_loop(t_shell *shell);
void				free_shell(t_shell *shell);
void				list_export(t_env *env);
void				list_env(t_env *env);
void				sort_env_list(t_env **env);
void				unset_env_variable(t_env **env, char *key);

t_env				*clone_env(char **envp);
t_env				*create_default_env(void);
t_env				*create_env_node(char *key, char *value);
t_env				*parse_env_entry(char *env_entry);
t_env				*clone_env_list(t_env *env);

#endif