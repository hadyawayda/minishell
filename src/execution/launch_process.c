#include "../lib/execution.h"

int    launch_external(char **argv, t_redir *redirs)
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
    {
        apply_redirs(redirs);
        execvp(argv[0], argv);
        perror("execvp");
        exit(127);
    }

    waitpid(pid, &wstatus, 0);
    if (WIFEXITED(wstatus))
        return WEXITSTATUS(wstatus);

    return 1;
}