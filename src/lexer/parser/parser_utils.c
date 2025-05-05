/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:22:15 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/05 20:22:58 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

t_job *malloc_job(void)
{
    t_job *job = malloc(sizeof *job);
    if (!job) return NULL;
    job->first = NULL;
    return job;
}

t_command *malloc_command(void)
{
    t_command *cmd = malloc(sizeof *cmd);
    if (!cmd) return NULL;
    cmd->argv      = NULL;
    cmd->redirs    = NULL;
    cmd->background= false;
    cmd->next      = NULL;
    return cmd;
}

char **append_argv(char **argv, const char *val)
{
    int   old = 0;
    char **newv;

    if (argv)
        while (argv[old])
            old++;

    newv = malloc(sizeof(char*) * (old + 2));
    if (!newv)
        return argv;

    for (int i = 0; i < old; i++)
        newv[i] = argv[i];

    newv[old]     = strdup(val);
    newv[old + 1] = NULL;
    free(argv);
    return newv;
}

int is_redir(t_tokentype t)
{
    return (t == T_REDIR_IN
         || t == T_REDIR_OUT
         || t == T_REDIR_APPEND
         || t == T_REDIR_HERE);
}

t_redir *malloc_redir(void)
{
    t_redir *r = malloc(sizeof *r);
    if (!r) return NULL;
    r->kind   = R_IN;
    r->target = NULL;
    r->next   = NULL;
    return r;
}

t_redir_kind map_to_redir_kind(t_tokentype t)
{
    if (t == T_REDIR_IN)     return R_IN;
    if (t == T_REDIR_OUT)    return R_OUT;
    if (t == T_REDIR_APPEND) return R_APPEND;
    if (t == T_REDIR_HERE)   return R_HERE;
    return R_IN;
}

void execute_job(t_job *job)
{
    (void)job;
}

void free_job(t_job *job)
{
    free(job);
}
