/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:23:42 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/12 23:00:34 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	count_opts(t_parser *p, int *n_opts)
{
	int		save;
	t_token	*tok;

	save = p->pos;
	*n_opts = 0;
	while (1)
	{
		tok = peek(p);
		if (tok->type == T_WORD)
		{
			next(p);
			if (tok->value[0] == '-' && !tok->is_quoted)
				(*n_opts)++;
		}
		else if (is_redir(tok->type))
		{
			next(p);
			if (tok->type != T_REDIR_HERE && peek(p)->type == T_WORD)
				next(p);
		}
		else
			break ;
	}
	p->pos = save;
}

/*–– 2) allocate and zero a t_ast + its leaf arrays ––*/
t_ast	*alloc_cmd_node(int n_opts)
{
	t_ast	*node;

	node = malloc(sizeof * node);
	ft_memset(node, 0, sizeof * node);
	node->type = N_CMD;
	node->cmd.command = NULL;
	node->cmd.redirs = NULL;
	node->cmd.args = NULL;
	node->cmd.options = malloc((n_opts + 1) * sizeof * node->cmd.options);
	ft_memset(node->cmd.options, 0, (n_opts + 1) * sizeof * node->cmd.options);
	return (node);
}

/*–– 3) parse a single redirection into a t_redir* ––*/
t_redir	*parse_redir(t_parser *p)
{
	t_token	*op_tok;
	t_redir	*r;
	t_token	*tgt;

	op_tok = next(p);
	r = malloc(sizeof * r);
	ft_memset(r, 0, sizeof * r);
	r->op = op_tok->type;
	if (r->op == T_REDIR_HERE)
	{
		if (op_tok->heredoc)
			r->target = ft_strdup(op_tok->heredoc);
		else
			r->target = ft_strdup("");
	}
	else
	{
		tgt = next(p);
		r->target = ft_strdup(tgt->value);
	}
	r->next = NULL;
	return (r);
}

/*–– helper: parse & attach one redirection to the list ––*/
void	handle_redir_token(t_parser *p, t_redir **rhead, t_redir **rtail)
{
	t_redir	*r;

	r = parse_redir(p);
	if (!*rhead)
		*rhead = r;
	else
		(*rtail)->next = r;
	*rtail = r;
}

/*–– 4) second pass: fill command, options[], args list, redirs ––*/
void	fill_cmd_node(t_parser *p, t_ast *node)
{
	t_token		*tok;
	t_redir		*rhead;
	t_redir		*rtail;
	t_argnode	*args_head;
	t_argnode	*args_tail;

	rhead = NULL;
	rtail = NULL;
	args_head = NULL;
	args_tail = NULL;
	while (1)
	{
		tok = peek(p);
		if (tok->type == T_WORD)
		{
			next(p);
			handle_word_token(node, tok, &args_head, &args_tail);
		}
		else if (is_redir(tok->type))
			handle_redir_token(p, &rhead, &rtail);
		else
			break ;
	}
	node->cmd.redirs = rhead;
	node->cmd.args = args_head;
}
