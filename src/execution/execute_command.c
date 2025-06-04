/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:18:00 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/04 14:20:06 by hawayda          ###   ########.fr       */
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

int    execute_cmd(t_shell *shell, t_ast *node)
{
    char        **argv;
    t_builtin   bi;
    int         status;

    argv = build_argv(node);
    if (argv == NULL)
        return 1;

    bi = get_builtin(argv[0]);
    if (bi != BI_NONE)
    {
        save_fds();
        apply_redirections(node->cmd.redirs);

        /*
        ** Example: you must implement run_builtin_*(shell, argv) yourself.
        ** Each case (BI_CD, BI_ECHO, etc.) can be an if/else chain,
        ** since we can’t use switch.
        */
        // if (bi == BI_CD)
        //     status = builtin_cd(shell, argv);
        // else if (bi == BI_ECHO)
        //     status = builtin_echo(shell, argv);
        // else if (bi == BI_PWD)
        //     status = builtin_pwd(shell, argv);
        // else if (bi == BI_EXPORT)
        //     status = builtin_export(shell, argv);
        // else if (bi == BI_UNSET)
        //     status = builtin_unset(shell, argv);
        // else /* BI_EXIT */
        //     status = builtin_exit(shell, argv);

        restore_fds();
    }
    else
    {
        status = launch_external(shell, argv, node->cmd.redirs);
    }

    free_argv(argv);
    return status;
}
