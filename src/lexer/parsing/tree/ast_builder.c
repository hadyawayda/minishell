/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 02:43:35 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/04 22:53:42 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/parser.h"

/*–– public: parse a single command leaf ––*/
t_ast	*parse_command(t_parser *p)
{
	t_ast	*node;
	int		n_opts;

	n_opts = 0;
	count_opts(p, &n_opts);
	node = alloc_cmd_node(n_opts);
	fill_cmd_node(p, node);
	return (node);
}

t_ast	*parse_factor(t_parser *p)
{
	t_ast	*sub;

	if (peek(p)->type == T_LPAREN)
	{
		next(p);
		sub = parse_expression(p);
		if (peek(p)->type != T_RPAREN)
			return (NULL);
		next(p);
		return (sub);
	}
	return (parse_command(p));
}

t_ast	*parse_pipe(t_parser *p)
{
	t_ast	*left;
	t_ast	*node;
	t_ast	*right;

	left = parse_factor(p);
	while (peek(p)->type == T_PIPE)
	{
		next(p);
		right = parse_factor(p);
		node = malloc(sizeof * node);
		ft_memset(node, 0, sizeof * node);
		node->type = N_PIPE;
		node->left = left;
		node->right = right;
		left = node;
	}
	return (left);
}

t_ast	*parse_expression(t_parser *p)
{
	t_ast		*left;
	t_ast		*node;
	t_node_type	kind;
	t_ast		*right;

	left = parse_pipe(p);
	while (peek(p)->type == T_AND || peek(p)->type == T_OR)
	{
		if (peek(p)->type == T_AND)
			kind = N_AND;
		else if (peek(p)->type == T_OR)
			kind = N_OR;
		next(p);
		right = parse_pipe(p);
		node = malloc(sizeof * node);
		ft_memset(node, 0, sizeof * node);
		node->type = kind;
		node->left = left;
		node->right = right;
		left = node;
	}
	return (left);
}

t_ast	*build_ast(t_token *tokens)
{
	t_parser	parser;

	parser.tokens = tokens;
	parser.pos = 0;
	return (parse_expression(&parser));
}
