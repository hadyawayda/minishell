/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:17:52 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/12 23:00:34 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
 * Free a linked list of t_redir:
 *   • free r->target (string),
 *   • free the node itself.
 */
static void	free_redirs(t_redir *rhead)
{
	t_redir	*tmp;

	while (rhead)
	{
		tmp = rhead->next;
		if (rhead->target)
			free(rhead->target);
		free(rhead);
		rhead = tmp;
	}
}

/*
 * Free a linked list of t_argnode:
 *   • free a->value (string),
 *   • free the node itself.
 */
static void	free_argnodes(t_argnode *ahead)
{
	t_argnode	*tmp;

	while (ahead)
	{
		tmp = ahead->next;
		if (ahead->value)
			free(ahead->value);
		free(ahead);
		ahead = tmp;
	}
}

/*
 * Free the NULL‐terminated options[] array in a t_cmd_leaf:
 *   • free each options[i] (string),
 *   • free the array itself.
 */
static void	free_options(char **opts)
{
	int	i;

	if (!opts)
		return ;
	i = 0;
	while (opts[i])
	{
		free(opts[i]);
		i++;
	}
	free(opts);
}

/*
 * Free everything inside a t_cmd_leaf:
 *   • command (string),
 *   • options[] array,
 *   • args (linked list),
 *   • redirs (linked list).
 */
static void	free_cmd_leaf(t_cmd_leaf *cmd)
{
	if (!cmd)
		return ;
	if (cmd->command)
		free(cmd->command);
	free_options(cmd->options);
	free_argnodes(cmd->args);
	free_redirs(cmd->redirs);
}

/*
 * Recursively free the entire AST:
 *   1) postorder free left subtree
 *   2) postorder free right subtree
 *   3) if this is a leaf (N_CMD), free its t_cmd_leaf contents
 *   4) free the t_ast node itself
 */
void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->type == N_CMD)
		free_cmd_leaf(&node->cmd);
	free(node);
}
