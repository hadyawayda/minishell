/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:13:59 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/27 21:03:07 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

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
