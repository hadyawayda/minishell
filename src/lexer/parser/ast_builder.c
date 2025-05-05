/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 02:43:35 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/14 21:17:07 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

t_job *parse_tokens(t_token tokens[])
{
    int i = 0;
    t_job *job = malloc_job();
    t_command *cmd = malloc_command();
    job->first = cmd;

    while (tokens[i].type != END_TOKEN)
    {
        if (tokens[i].type == T_WORD)
            cmd->argv = append_argv(cmd->argv, tokens[i++].value);
        else if (is_redir(tokens[i].type))
        {
            t_redir *r = malloc_redir();
            r->kind   = map_to_redir_kind(tokens[i].type);
            i++;
            r->target = (r->kind == R_HERE)
                        ? strdup(tokens[i].heredoc)
                        : strdup(tokens[i].value);
            r->next   = cmd->redirs;
            cmd->redirs = r;
            i++;
        }
        else if (tokens[i].type == T_PIPE)
        {
            i++;
            cmd->next = malloc_command();
            cmd = cmd->next;
        }
        else if (tokens[i].type == T_AND)
        {
            cmd->background = true;
            i++;
        }
        else
            i++;
    }

    return job;
}
