/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 02:43:35 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/05 20:19:00 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/* tokens[] must already have heredocs collected and syntax checked */
static int cur = 0;                 /* global index into tokens[]    */
static t_token *g;                  /* global pointer to array       */

/* Forward decls */
t_ast *parse_expr(void);            /* lowest precedence (AND/OR)    */
t_ast *parse_pipe(void);            /* pipeline level                */
t_ast *parse_factor(void);          /* command or parenthesised expr */
t_ast *parse_command(void);         /* simple cmd with redirs        */

static t_token *peek(void)  { return &g[cur]; }
static t_token *next(void)  { return &g[cur++]; }

t_ast *parse_expr(void)
{
    t_ast *left = parse_pipe();
    while (peek()->type == T_AND || peek()->type == T_OR)
    {
        t_node_type kind = (peek()->type == T_AND) ? N_AND : N_OR;
        next();                             /* consume && / ||        */
        t_ast *right = parse_pipe();
        t_ast *node  = calloc(1, sizeof *node);
        node->type   = kind;
        node->left   = left;
        node->right  = right;
        left = node;
    }
    return left;
}

t_ast *parse_pipe(void)
{
    t_ast *left = parse_factor();
    while (peek()->type == T_PIPE)
    {
        next();                             /* consume |              */
        t_ast *right = parse_factor();
        t_ast *node  = calloc(1, sizeof *node);
        node->type   = N_PIPE;
        node->left   = left;
        node->right  = right;
        left = node;
    }
    return left;
}

t_ast *parse_factor(void)
{
    if (peek()->type == T_LPAREN)
    {
        next();                             /* consume '('            */
        t_ast *sub = parse_expr();
        if (peek()->type != T_RPAREN)
            return NULL;                    /* unmatched ) – shouldn't happen
                                             * after syntax check     */
        next();                             /* consume ')'            */
        return sub;
    }
    return parse_command();                 /* leaf                   */
}

t_ast *parse_command(void)
{
    t_ast *node = calloc(1, sizeof *node);
    node->type  = N_CMD;

    /* dynamic argv builder */
    int    cap = 4, argc = 0;
    char **argv = malloc(sizeof(char*) * cap);

    t_redir *redir_head = NULL;
    t_redir *redir_tail = NULL;

    while (peek()->type == T_WORD || peek()->type == T_REDIR_IN
        || peek()->type == T_REDIR_OUT || peek()->type == T_REDIR_APPEND
        || peek()->type == T_REDIR_HERE)
    {
        if (peek()->type == T_WORD)                 /* argument token */
        {
            if (argc == cap)
            {
                cap *= 2;
                argv = realloc(argv, sizeof(char*) * cap);
            }
            argv[argc++] = strdup(next()->value);
        }
        else                                        /* redirection op */
        {
            t_tokentype op = next()->type;          /* eat < , > , …  */
            t_token *target_tok = next();           /* the WORD after */
            t_redir *r = calloc(1, sizeof *r);
            r->op     = op;
            if (op == T_REDIR_HERE)
                r->target = strdup(target_tok->heredoc);
            else
                r->target = strdup(target_tok->value);

            if (!redir_head) redir_head = r;
            else             redir_tail->next = r;
            redir_tail = r;
        }
    }
    argv[argc]      = NULL;

    node->cmd.argv  = argv;
    node->cmd.redirs= redir_head;
    return node;
}

/* public entry: build tree from tokens[] */
t_ast *build_ast(t_token *tokens)
{
    g   = tokens;
    cur = 0;
    return parse_expr();    /* root of the tree */
}
