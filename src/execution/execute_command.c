#include "../lib/execution.h"

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
        apply_redirs(node->cmd.redirs);

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
        status = launch_external(argv, node->cmd.redirs);
    }

    free_argv(argv);
    return status;
}
