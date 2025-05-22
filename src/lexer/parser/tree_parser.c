/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:13:59 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/13 00:33:41 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/**
 * expand_wildcards()
 *
 * In the future: for each argv[i] where expandable[i] == true,
 * scan the filesystem for matches and splice them into a new argv[].
 *
 * For now it’s a no-op.
 */
char **expand_wildcards(char **arguments, bool *expandable)
{
  (void)arguments;
  (void)expandable;
  return arguments;
}

/**
 * tree_parser()
 * 
 * Walk the AST. For each command leaf, apply expand_wildcards
 * to the arguments array (no-op for now).
 */
void tree_parser(t_ast *root)
{
    if (!root)
        return;
    // if (root->type == N_CMD)
    // {
    //     root->cmd.arguments = expand_wildcards(
    //     root->cmd.arguments,
    //     root->cmd.expandable
    //     );
    // }
    // else
    // {
    //     tree_parser(root->left);
    //     tree_parser(root->right);
    // }
}
