#include "../lib/execution.h"

char    **build_argv(t_ast *node)
{
    char        **argv;
    t_argnode   *argnode;
    int         nopt;
    int         nargs;
    int         total;
    int         i;

    nopt = 0;
    while (node->cmd.options[nopt] != NULL)
        nopt++;

    nargs = 0;
    argnode = node->cmd.args;
    while (argnode != NULL)
    {
        nargs++;
        argnode = argnode->next;
    }

    total = 1 + nopt + nargs + 1;
    argv = malloc(sizeof(char *) * total);
    if (argv == NULL)
        return NULL;

    i = 0;
    argv[i] = ft_strdup(node->cmd.command);
    i++;

    nopt = 0;
    while (node->cmd.options[nopt] != NULL)
    {
        argv[i] = ft_strdup(node->cmd.options[nopt]);
        i++;
        nopt++;
    }

    argnode = node->cmd.args;
    while (argnode != NULL)
    {
        argv[i] = ft_strdup(argnode->value);
        i++;
        argnode = argnode->next;
    }

    argv[i] = NULL;
    return argv;
}

/* Free a null-terminated array of strings */
void    free_argv(char **argv)
{
    int    i;

    i = 0;
    if (argv == NULL)
        return;

    while (argv[i] != NULL)
    {
        free(argv[i]);
        i++;
    }
    free(argv);
}
