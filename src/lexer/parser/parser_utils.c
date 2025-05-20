/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:22:15 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/07 18:51:59 by hawayda          ###   ########.fr       */
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

void free_ast(t_ast *node)
{
	if (node != NULL)
	{
		free_ast(node->left);
		free_ast(node->right);
	}
	free(node);
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

void	print_tokens(t_token *tokens)
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
