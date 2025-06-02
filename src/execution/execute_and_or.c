#include "../lib/execution.h"

/*
** For N_AND: if left returns 0, run right; else return left’s status.
*/
int    execute_and(t_shell *shell, t_ast *node)
{
    int    st;

    st = execute_ast(shell, node->left);
    if (st == 0)
        return execute_ast(shell, node->right);

    return st;
}

/*
** For N_OR: if left returns nonzero, run right; else return left’s status.
*/
int    execute_or(t_shell *shell, t_ast *node)
{
    int    st;

    st = execute_ast(shell, node->left);
    if (st != 0)
        return execute_ast(shell, node->right);

    return st;
}
