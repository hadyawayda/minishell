#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

char      **build_argv(t_ast *node);

int    execute_and(t_shell *shell, t_ast *node);
int    execute_or(t_shell *shell, t_ast *node);
int    execute_cmd(t_shell *shell, t_ast *node);
int    execute_pipe(t_shell *shell, t_ast *node);
int    execute_ast(t_shell *shell, t_ast *node);
int    launch_external(char **argv, t_redir *redirs);

void    free_argv(char **argv);
void    save_fds(void);
void    restore_fds(void);
void    apply_redirs(t_redir *redirs);

t_builtin   get_builtin(char *cmd);

#endif
