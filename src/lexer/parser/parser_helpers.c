/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:22:15 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/22 23:23:29 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

t_token	*peek(t_parser *p)
{
	return (&p->tokens[p->pos]);
}

t_token	*next(t_parser *p)
{
	return (&p->tokens[p->pos++]);
}

void	free_tokens(t_token *tokens)
{
	int		i;
	bool	*shared_flags;

	shared_flags = tokens[0].is_expandable;
	i = 0;
	while (tokens[i].type != (t_tokentype)-1)
	{
		free(tokens[i].value);
		free(tokens[i].heredoc);
		i++;
	}
	free(shared_flags);
	free(tokens);
}

void	free_ast(t_ast *node)
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

	i = 0;
	while (tokens[i].type != (t_tokentype) -1)
	{
		if (tokens[i].type == T_REDIR_HERE && tokens[i].heredoc)
			printf("%s", tokens[i].heredoc);
		else
			printf("%s", tokens[i].value);
		if (tokens[i + 1].type != (t_tokentype) - 1)
			putchar(' ');
		i++;
	}
	putchar('\n');
}
