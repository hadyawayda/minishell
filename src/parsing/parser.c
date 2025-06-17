/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:27:30 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/17 23:55:39 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*parser(t_shell *shell, t_token *tokens)
{
	t_ast	*root;

	if (!tokens)
		return (NULL);
	if ((check_syntax(tokens) < 0) || (collect_heredocs(shell, tokens) < 0))
	{
		free_tokens(tokens);
		return (NULL);
	}
	root = build_ast(tokens);
	free_tokens(tokens);
	return (root);
}

// debugging helper functions that can be called:
// print_tokens(tokens);
// visualize_heredoc_tokens(tokens);
// visualize_tree(root);
