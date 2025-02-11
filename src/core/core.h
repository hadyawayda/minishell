#include "../../includes/minishell.h"
#include "../parser/parser.h"
#include <stdlib.h>
#include <string.h>

#ifndef CORE_H
# define CORE_H

void				free_env(t_env *env);
void				minishell(char **env);
void				shell_loop(t_shell *shell);
void				free_shell(t_shell *shell);
void				list_export(t_env *env);
void				list_env(t_env *env);
void				sort_env_list(t_env **env);

t_env				*clone_env(char **envp);
t_env				*create_default_env(void);
t_env				*create_env_node(char *key, char *value);
t_env				*parse_env_entry(char *env_entry);

#endif