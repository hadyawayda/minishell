/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 02:43:35 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/13 00:25:23 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/* tokens[] must already have heredocs collected and syntax checked */
static int			g_pos = 0; /* global index into tokens[]    */
static t_token	*g_tokens;  /* global pointer to array       */

static t_token *peek(void)
{
    return (&g_tokens[g_pos]);
}

static t_token *next(void)
{
    return (&g_tokens[g_pos++]);
}

static inline int is_redir(t_tokentype t)
{
    return (t == T_REDIR_IN
         || t == T_REDIR_OUT
         || t == T_REDIR_APPEND
         || t == T_REDIR_HERE);
}

static void count_opts(int *n_opts)
{
    t_token *tok;
    int      save = g_pos;

    *n_opts = 0;
    while ((tok = peek())->type == T_WORD || is_redir(tok->type))
    {
        if (tok->type == T_WORD)
        {
            next();
            if (tok->value[0] == '-' && !tok->is_quoted)
                (*n_opts)++;
        }
        else
        {
            next();
            if (peek()->type == T_WORD)
                next();
        }
    }
    g_pos = save;
}

/*–– 2) allocate and zero a t_ast + its leaf arrays ––*/
static t_ast *alloc_cmd_node(int n_opts)
{
    t_ast *node = malloc(sizeof *node);

    ft_memset(node, 0, sizeof *node);
    node->type            = N_CMD;
    node->cmd.command     = NULL;
    node->cmd.redirs      = NULL;
    node->cmd.args        = NULL;
    node->cmd.options     = malloc((n_opts + 1) * sizeof *node->cmd.options);
    ft_memset(node->cmd.options, 0, (n_opts + 1) * sizeof *node->cmd.options);
    return (node);
}

/*–– 3) parse a single redirection into a t_redir* ––*/
static t_redir *parse_redir(void)
{
	t_tokentype op = next()->type;
	t_redir    *r = malloc(sizeof *r);

	ft_memset(r, 0, sizeof *r);
	r->op = op;
	if (op == T_REDIR_HERE)
		r->target = ft_strdup(g_tokens[g_pos - 1].heredoc);
	else
		r->target = ft_strdup(next()->value);
	r->next = NULL;
	return r;
}

static void handle_word_token(t_ast *node,
    t_token *tok, int *opt_i, t_argnode **args_head, t_argnode **args_tail)
{
    t_argnode *an;

    if (!node->cmd.command)
        node->cmd.command = ft_strdup(tok->value);
    else if (tok->value[0] == '-' && !tok->is_quoted)
        node->cmd.options[(*opt_i)++] = ft_strdup(tok->value);
    else
    {
        an = malloc(sizeof *an);
        ft_memset(an, 0, sizeof *an);
        an->value      = ft_strdup(tok->value);
        an->expandable = !tok->is_quoted;
        an->next       = NULL;
        if (!*args_head)
            *args_head = an;
        else
            (*args_tail)->next = an;
        *args_tail = an;
    }
}

/*–– helper: parse & attach one redirection to the list ––*/
static void handle_redir_token(t_redir **rhead, t_redir **rtail)
{
    t_redir *r = parse_redir();

    r->next = NULL;
    if (!*rhead)
        *rhead = r;
    else
        (*rtail)->next = r;
    *rtail = r;
}

/*–– 4) second pass: fill command, options[], args list, redirs ––*/
static void fill_cmd_node(t_ast *node)
{
    t_token   *tok;
    int        opt_i = 0;
    t_redir   *rhead = NULL;
    t_redir   *rtail = NULL;
    t_argnode *args_head = NULL;
    t_argnode *args_tail = NULL;

    while ((tok = peek())->type == T_WORD || is_redir(tok->type))
    {
        if (tok->type == T_WORD)
        {
            tok = next();
            handle_word_token(node, tok,
                &opt_i, &args_head, &args_tail);
        }
        else
        {
            handle_redir_token(&rhead, &rtail);
        }
    }
    node->cmd.options[opt_i] = NULL;
    node->cmd.redirs         = rhead;
    node->cmd.args           = args_head;
}

/*–– public: parse a single command leaf ––*/
t_ast *parse_command(void)
{
    int n_opts, n_args;

		count_opts(&n_opts);
    t_ast *node = alloc_cmd_node(n_opts);
    fill_cmd_node(node);
    return node;
}

t_ast	*parse_factor(void)
{
	t_ast	*sub;

	if (peek()->type == T_LPAREN)
	{
		next(); /* consume '('            */
		sub = parse_expr();
		if (peek()->type != T_RPAREN)
			return (NULL); /* unmatched ) – shouldn't happen
							* after syntax check     */
		next();          /* consume ')'            */
		return (sub);
	}
	return (parse_command()); /* leaf                   */
}

t_ast	*parse_pipe(void)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*node;

	left = parse_factor();
	while (peek()->type == T_PIPE)
	{
		next(); /* consume |              */
		right = parse_factor();
		node  = malloc(sizeof *node);
		ft_memset(node, 0, sizeof *node);
		node->type = N_PIPE;
		node->left = left;
		node->right = right;
		left = node;
	}
	return (left);
}

t_ast	*parse_expr(void)
{
	t_ast		*left;
	t_node_type	kind;
	t_ast		*right;
	t_ast		*node;

	left = parse_pipe();
	while (peek()->type == T_AND || peek()->type == T_OR)
	{
		kind = (peek()->type == T_AND) ? N_AND : N_OR;
		next(); /* consume && / ||        */
		right = parse_pipe();
		node  = malloc(sizeof *node);
		ft_memset(node, 0, sizeof *node);
		node->type = kind;
		node->left = left;
		node->right = right;
		left = node;
	}
	return (left);
}

/* public entry: build tree from tokens[] */
t_ast *build_ast(t_token *tokens)
{
    g_tokens = tokens;
    g_pos    = 0;
    return (parse_expr());
}