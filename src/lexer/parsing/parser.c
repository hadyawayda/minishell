/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:27:30 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/03 17:29:44 by hawayda          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../lib/parser.h"

t_ast	*parser(t_shell *shell, t_token *tokens)
{
	t_ast	*root;

	if (!tokens)
		return (NULL);
	if (check_syntax(tokens) < 0)
	{
		free_tokens(tokens);
		return (NULL);
	}
	collect_heredocs(shell, tokens);
	// print_tokens(tokens);
	// visualize_heredoc_tokens(tokens);
	root = build_ast(tokens);
	// visualize_tree(root);
	free_tokens(tokens);
	return (root);
}
