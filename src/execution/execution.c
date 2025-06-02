/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:55:40 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/30 21:12:56 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/parser.h"

/**
 * tree_parser()
 *
 * Walk the AST. For each command leaf, apply expand_wildcards
 * to the arguments array (no-op for now).
 */
void	tree_parser(t_ast *root)
{
	if (!root)
		return ;
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
