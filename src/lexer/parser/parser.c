/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:13:59 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/12 23:44:04 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	free_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != (t_tokentype)-1)
	{
		free(tokens[i].value);
		i++;
	}
	free(tokens);
}

void	visualize_heredoc_tokens(t_token tokens[])
{
	int	i;

	for (i = 0; tokens[i].type != (t_tokentype)-1; i++)
	{
		if (tokens[i].type == T_REDIR_HERE && tokens[i].heredoc)
			printf("%s", tokens[i].heredoc);
		else
			printf("%s", tokens[i].value);
		if (tokens[i + 1].type != (t_tokentype)-1)
			putchar(' ');
	}
	putchar('\n');
}

static void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != (t_tokentype)-1)
	{
		printf("%s", tokens[i].value);
		if (tokens[i + 1].type != (t_tokentype)-1)
			printf(" ");
		i++;
	}
	printf("\n");
}

void free_ast(t_ast *node)
{
	if (node != NULL)
	{
		free_ast(node->left);
		free_ast(node->right);
	}
	free(node);
}

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
	// print_tokens(tokens);
	// visualize_heredoc_tokens(tokens);
	root = build_ast(tokens);
	// visualize_tree(root);
	// traverse_ast(root);
	free_tokens(tokens);
	free_ast(root);
}

// echo $USER | cat <<b | echo hello | cat << c | echo hi

/* width of the top bar */

// #define COL_W 23
// #define COL_GAP 4
