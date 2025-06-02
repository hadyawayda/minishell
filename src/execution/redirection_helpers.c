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
** Walk the t_redir linked list. For each redirect:
**   - open the target file (O_RDONLY, O_WRONLY|O_CREAT|O_TRUNC, or O_APPEND)
**   - dup2 into STDIN or STDOUT
**   - close the opened fd
*/
void    apply_redirs(t_redir *redirs)
{
    int    fd;

    while (redirs != NULL)
    {
        if (redirs->op == T_REDIR_IN)
        {
            fd = open(redirs->target, O_RDONLY);
            if (fd < 0)
            {
                perror(redirs->target);
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (redirs->op == T_REDIR_OUT)
        {
            fd = open(redirs->target,
                      O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror(redirs->target);
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redirs->op == T_REDIR_APPEND)
        {
            fd = open(redirs->target,
                      O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
            {
                perror(redirs->target);
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redirs->op == T_REDIR_HERE)
        {
            /* 
            ** Assume `target` holds a temporary filename created by
            ** collect_heredocs(). Open it read-only and dup2 into STDIN.
            */
            fd = open(redirs->target, O_RDONLY);
            if (fd < 0)
            {
                perror(redirs->target);
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        redirs = redirs->next;
    }
}
