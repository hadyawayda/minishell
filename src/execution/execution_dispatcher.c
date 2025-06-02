#include "../lib/execution.h"

/*
** Walk the AST. No switch/case—just if/else if. Return each subtree’s exit code.
*/
int    execute_ast(t_shell *shell, t_ast *node)
{
    if (node == NULL)
        return 0;

    if (node->type == N_CMD)
        return execute_cmd(shell, node);

    else if (node->type == N_PIPE)
        return execute_pipe(shell, node);

    else if (node->type == N_AND)
        return execute_and(shell, node);

    else if (node->type == N_OR)
        return execute_or(shell, node);

    return 0;
}
