/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:18:00 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/04 20:08:17 by hawayda          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../lib/execution.h"

static int   saved_stdin;
static int   saved_stdout;

/*
** Before applying any redir for a builtin, call this once
** (it dups STDIN_FILENO / STDOUT_FILENO to static vars).
*/
void    save_fds(void)
{
    if (saved_stdin < 0)
        saved_stdin = dup(STDIN_FILENO);
    if (saved_stdout < 0)
        saved_stdout = dup(STDOUT_FILENO);
}

/*
** Restore the saved FDs (if they were saved). Then close the copies.
*/
void    restore_fds(void)
{
    if (saved_stdin >= 0)
    {
        dup2(saved_stdin, STDIN_FILENO);
        close(saved_stdin);
        saved_stdin = -1;
    }
    if (saved_stdout >= 0)
    {
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        saved_stdout = -1;
    }
}

/*
** If `bi` corresponds to a custom builtin, run it and exit with its status.
** Otherwise, simply return (caller will continue to execve).
*/
void    handle_custom_builtin(t_shell *sh, t_builtin bi, char **argv)
{
    // if (bi == BI_CD)
    //     exit(builtin_cd(sh, argv));
    // else if (bi == BI_PWD)
    //     exit(builtin_pwd(sh, argv));
    // else if (bi == BI_ECHO)
    //     exit(builtin_echo(sh, argv));
    // else if (bi == BI_ENV)
    //     exit(builtin_env(sh, argv));
    // else if (bi == BI_EXPORT)
    //     exit(builtin_export(sh, argv));
    // else if (bi == BI_UNSET)
    //     exit(builtin_unset(sh, argv));
    // else if (bi == BI_EXIT)
    //     exit(builtin_exit(sh, argv));
}

/*
** Called only inside a forked child. 
**   - First apply ANY redirections for this node (">", "<", ">>", "<<").  
**   - Then either run a builtin in‐process, or do execve()/exit.  
** Note: sys-builtins (like /bin/echo) are covered by execve; 
** your “custom builtins” get integrated here.
*/
void    exec_cmd_in_child(t_shell *sh, t_ast *node)
{
    char      **argv;
    char      **envp;
    t_builtin bi;

    argv = build_argv(node);
    if (argv == NULL)
        exit(1);
    apply_redirections(node->cmd.redirs);
    bi = get_builtin(argv[0]);
    handle_custom_builtin(sh, bi, argv);
    envp = build_envp(sh->env);
    execve(find_executable(sh, argv[0]), argv, envp);
    ft_putstr_fd(argv[0], STDERR_FILENO);
    ft_putstr_fd(": command not found\n", STDERR_FILENO);
    if (envp)
        free_argv(envp);
    free_argv(argv);
    exit(127);
}

/*
** For a single N_CMD node when NOT in a pipeline, we still fork once
** so that builtins and execve happen in the child. The parent only waits.
*/
int    execute_cmd(t_shell *shell, t_ast *node)
{
    pid_t   pid;
    int     wstatus;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    else if (pid == 0)
        exec_cmd_in_child(shell, node);
    waitpid(pid, &wstatus, 0);
    if (WIFEXITED(wstatus))
        return WEXITSTATUS(wstatus);
    return 1;
}
