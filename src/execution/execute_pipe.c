#include "../lib/execution.h"

/*
** For a PIPE node, we:
**   1. Create pipefd[2].
**   2. Fork left child:
**       - dup2(pipefd[1], STDOUT), close both ends, exit(execute_ast(left)).
**   3. Fork right child:
**       - dup2(pipefd[0], STDIN), close both ends, exit(execute_ast(right)).
**   4. Parent closes both ends, waits for both, returns right’s status.
*/
int    execute_pipe(t_shell *shell, t_ast *node)
{
    int     pipefd[2];
    pid_t   left_pid;
    pid_t   right_pid;
    int     left_stat;
    int     right_stat;

    if (pipe(pipefd) < 0)
    {
        perror("pipe");
        return 1;
    }

    left_pid = fork();
    if (left_pid < 0)
    {
        perror("fork");
        return 1;
    }
    else if (left_pid == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        exit(execute_ast(shell, node->left));
    }

    right_pid = fork();
    if (right_pid < 0)
    {
        perror("fork");
        return 1;
    }
    else if (right_pid == 0)
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        exit(execute_ast(shell, node->right));
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(left_pid, &left_stat, 0);
    waitpid(right_pid, &right_stat, 0);

    if (WIFEXITED(right_stat))
        return WEXITSTATUS(right_stat);

    return 1;
}
