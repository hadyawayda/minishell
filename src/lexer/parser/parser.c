/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:13:59 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/13 00:33:41 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

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
	// collect_heredocs(shell, tokens);
	print_tokens(tokens);
	// visualize_heredoc_tokens(tokens);
	// root = build_ast(tokens);
	// visualize_tree(root);
	// traverse_ast(root);
	free_tokens(tokens);
	// free_ast(root);
}

// echo $USER | cat <<b | echo hello | cat << c | echo hi

/* width of the top bar */

// #define COL_W 23
// #define COL_GAP 4
