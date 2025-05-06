/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 02:43:35 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/05 20:19:00 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void traverse_ast(t_ast *n)
{
    if (!n) return;
    if (n->type == N_CMD)
    {
        printf("[CMD]");
        for (int i = 0; n->cmd.argv[i]; i++)
            printf(" %s", n->cmd.argv[i]);
        printf("\n");
    }
    else
    {
        traverse_ast(n->left);
        if (n->type == N_PIPE) puts("[PIPE]");
        else if (n->type == N_AND) puts("[AND]");
        else puts("[OR]");
        traverse_ast(n->right);
    }
}
