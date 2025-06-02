/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:13:59 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/28 23:17:37 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/parser.h"

void	parser(t_shell *shell, t_token *tokens)
{
	t_ast	*root;

	if (!tokens)
		return ;
	if (check_syntax(tokens) < 0)
	{
		free_tokens(tokens);
		return ;
	}
	collect_heredocs(shell, tokens);
	print_tokens(tokens);
	// visualize_heredoc_tokens(tokens);
	// root = build_ast(tokens);
	// tree_parser(root);
	// visualize_tree(root);
	free_tokens(tokens);
	// execute_ast(root);
	// move tree traversal to execute_ast();
	// // traverse_ast(root);
}
