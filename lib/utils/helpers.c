/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:38:23 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/12 23:33:35 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* src/lexer/parser/tree_visualizer.c */
#include "execution.h"
#include <math.h>

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

void	visualize_heredoc_tokens(t_token tokens[])
{
	int	i;

	i = 0;
	while (tokens[i].type != (t_tokentype)-1)
	{
		if (tokens[i].type == T_REDIR_HERE && tokens[i].heredoc)
			printf("%s", tokens[i].heredoc);
		else
			printf("%s", tokens[i].value);
		if (tokens[i + 1].type != (t_tokentype)-1)
			putchar(' ');
		i++;
	}
	putchar('\n');
}

// static const char *g_token_names[] = {
//     [T_WORD]          = "WORD",
//     [T_PIPE]          = "PIPE",
//     [T_AND]           = "AND",
//     [T_OR]            = "OR",
//     [T_REDIR_IN]      = "REDIR_IN",
//     [T_REDIR_OUT]     = "REDIR_OUT",
//     [T_REDIR_HERE]    = "HEREDOC",
//     [T_REDIR_APPEND]  = "APPEND",
//     [T_LPAREN]        = "LPAREN",
//     [T_RPAREN]        = "RPAREN",
// };

// void print_tokens(t_token *tokens)
// {
//     int i = 0;
//     while (tokens[i].type != (t_tokentype)-1)
//     {
//         const char *name = g_token_names[tokens[i].type] ?: "UNK";
//         printf("%s(%s)", name, tokens[i].value);
//         if (tokens[i+1].type != (t_tokentype)-1)
//             printf(" ");
//         i++;
//     }
//     printf("\n");
// }

#define MAX_LABEL 256
#define HSP 6 /* horizontal spacing between subtrees */
#define VSP 4 /* vertical spacing per generation   */
#define LEFT_MARGIN "\t\t" /* indent before the diagram         */

static void	build_cmd_label(t_ast *n, char *buf, int cap)
{
	int		ai;
	char	ln[64];

	/* build a multi-line description:                  *
		*  cmd: <name>\noptions: -l -a\narg1: foo (yes)\n   *
		*  redir: > out.txt   /  heredoc etc.              */
	ai = 1;
	ft_bzero(buf, cap);
	ft_strlcat(buf, "cmd: ", cap);
	ft_strlcat(buf, n->cmd.command ? n->cmd.command : "(none)", cap);
	if (n->cmd.options && n->cmd.options[0])
		ft_strlcat(buf, "\noptions:", cap);
	for (int i = 0; n->cmd.options[i]; i++)
	{
		ft_strlcat(buf, " ", cap);
		ft_strlcat(buf, n->cmd.options[i], cap);
	}
	ft_strlcat(buf, "\n", cap);
	for (t_argnode *a = n->cmd.args; a; a = a->next, ai++)
	{
		snprintf(ln, sizeof ln, "arg%d: %s (%s)\n", ai, a->value,
			a->expandable ? "yes" : "no");
		ft_strlcat(buf, ln, cap);
	}
	for (t_redir *r = n->cmd.redirs; r; r = r->next)
	{
		if (r->op == T_REDIR_HERE)
			ft_strlcat(buf, "heredoc\n", cap);
		else
		{
			ft_strlcat(buf, "redir: ", cap);
			if (r->op == T_REDIR_IN)
				ft_strlcat(buf, "<  ", cap);
			else if (r->op == T_REDIR_OUT)
				ft_strlcat(buf, ">  ", cap);
			else
				ft_strlcat(buf, ">> ", cap);
			ft_strlcat(buf, r->target, cap);
			ft_strlcat(buf, "\n", cap);
		}
	}
	/* strip the very last '\n' so the loop that prints lines
		stops correctly */
	if (buf[ft_strlen(buf) - 1] == '\n')
		buf[ft_strlen(buf) - 1] = '\0';
}

static void	get_label(t_ast *n, char *buf, int buf_sz)
{
	if (n->type == N_CMD)
		build_cmd_label(n, buf, buf_sz);
	else if (n->type == N_PIPE)
		ft_strlcpy(buf, "|", buf_sz);
	else if (n->type == N_AND)
		ft_strlcpy(buf, "&&", buf_sz);
	else
		ft_strlcpy(buf, "||", buf_sz);
}

static int	label_height(t_ast *n)
{
	char	buf[MAX_LABEL];
	int		lines;

	get_label(n, buf, sizeof buf);
	lines = 1;
	for (char *p = buf; *p; ++p)
		if (*p == '\n')
			++lines;
	return (lines);
}

static int	subtree_height(t_ast *n)
{
	int	my_h;
	int	lh;
	int	rh;
	int	ch;

	if (!n)
		return (0);
	my_h = label_height(n);
	if (!n->left && !n->right)
		return (my_h);
	lh = subtree_height(n->left);
	rh = subtree_height(n->right);
	ch = lh > rh ? lh : rh;
	return (my_h + VSP + ch);
}

/* copy a label that may contain embedded ‘\n’ over several rows  */
static void	put_multiline(char **cv, int row, int col, const char *lbl)
{
	int	r;
	int	c;

	r = row;
	c = col;
	while (*lbl)
	{
		if (*lbl == '\n')
		{
			++r;
			c = col;
		}
		else if (r >= 0 && cv[r] && c >= 0)
		{
			cv[r][c] = *lbl;
			++c;
		}
		++lbl;
	}
}

/* return the number of columns a subtree needs (widest line only) */
static int	subtree_width(t_ast *n)
{
	char	lbl[MAX_LABEL];
	int		max_line;
	int		cur;
	int		lw;
	int		rw;
	int		spread;

	if (!n)
		return (0);
	get_label(n, lbl, sizeof lbl);
	/* --- longest line inside the multi-line block --- */
	max_line = cur = 0;
	for (int i = 0; lbl[i]; ++i)
	{
		if (lbl[i] == '\n')
		{
			if (cur > max_line)
				max_line = cur;
			cur = 0;
		}
		else
			++cur;
	}
	if (cur > max_line)
		max_line = cur;
	/* children widen the node if necessary */
	if (n->left || n->right)
	{
		lw = subtree_width(n->left);
		rw = subtree_width(n->right);
		spread = lw + HSP + rw;
		if (spread > max_line)
			max_line = spread;
	}
	return (max_line);
}

/* 4) Render with diagonal “/” and “\” */
/* recursive painter: centres block by longest internal line          */
static void	render_rec(t_ast *n, char **canvas, int row, int left, int right)
{
	char	lbl[MAX_LABEL];
	int		longest;
	int		mid;
	int		start;
	int		lw;
	int		cl;
	int		cr;
	int		cm;
	int		dc;
	int		r;
	int		off;
	int		c;
	int		rw;
	int		cur;

	longest = 0, cur;
	if (!n)
		return ;
	/* ---- prepare the multi-line label ---- */
	get_label(n, lbl, sizeof lbl);
	/* longest line inside lbl */
	longest = 0, cur = 0;
	for (int i = 0; lbl[i]; ++i)
	{
		if (lbl[i] == '\n')
		{
			if (cur > longest)
				longest = cur;
			cur = 0;
		}
		else
			++cur;
	}
	if (cur > longest)
		longest = cur;
	/* centre that block */
	mid = (left + right) / 2;
	start = mid - longest / 2;
	if (start < left)
		start = left;
	if (start + longest > right + 1)
		start = right + 1 - longest;
	put_multiline(canvas, row, start, lbl);
	/* ---- draw children ---- */
	if (n->left)
	{
		lw = subtree_width(n->left);
		cl = left;
		cr = left + lw - 1;
		cm = (cl + cr) / 2;
		dc = mid - cm;
		for (int i = 1; i <= VSP; ++i)
		{
			r = row + i;
			off = (int)round((double)dc * i / VSP);
			c = mid - off;
			canvas[r][c] = '/';
		}
		render_rec(n->left, canvas, row + VSP + 1, cl, cr);
	}
	if (n->right)
	{
		rw = subtree_width(n->right);
		cl = right - rw + 1;
		cr = right;
		cm = (cl + cr) / 2;
		dc = cm - mid;
		for (int i = 1; i <= VSP; ++i)
		{
			r = row + i;
			off = (int)round((double)dc * i / VSP);
			c = mid + off;
			canvas[r][c] = '\\';
		}
		render_rec(n->right, canvas, row + VSP + 1, cl, cr);
	}
}

/* 5) Public entry: build canvas, render, print, then dump details */
void	visualize_tree(t_ast *root)
{
	int		rows;
	int		cols;
	char	**canvas;

	if (!root)
		return ;
	rows = subtree_height(root);
	cols = subtree_width(root);
	canvas = calloc(rows, sizeof *canvas);
	for (int r = 0; r < rows; ++r)
	{
		canvas[r] = calloc(cols + 1, 1);
		memset(canvas[r], ' ', cols);
	}
	render_rec(root, canvas, 0, 0, cols - 1);
	putchar('\n');
	printf(LEFT_MARGIN "\n\n");
	for (int r = 0; r < rows; ++r)
		printf(LEFT_MARGIN "%s\n", canvas[r]);
	printf(LEFT_MARGIN "\n\n");
	for (int r = 0; r < rows; ++r)
		free(canvas[r]);
	free(canvas);
}

/* helper: make a one‐node arg list */
// static t_argnode *argnode(const char *val, bool exp)
// {
//     t_argnode *n = malloc(sizeof *n);
//     n->value      = strdup(val);
//     n->expandable = exp;
//     n->next       = NULL;
//     return (n);
// }

// /* helper: make a CMD leaf with no options/redirs */
// static t_ast *cmd_node(const char *cmd, t_argnode *args)
// {
//     t_ast *n = malloc(sizeof *n);
//     memset(n, 0, sizeof *n);
//     n->type           = N_CMD;
//     n->left           = n->right = NULL;
//     n->cmd.command    = strdup(cmd);
//     /* no options: single NULL */
//     n->cmd.options    = malloc(sizeof *n->cmd.options);
//     n->cmd.options[0] = NULL;
//     n->cmd.args       = args;
//     n->cmd.redirs     = NULL;
//     return (n);
// }

// /* helper: make a binary node (PIPE/AND/OR) */
// static t_ast *op_node(t_node_type type, t_ast *l, t_ast *r)
// {
//     t_ast *n = malloc(sizeof *n);
//     memset(n, 0, sizeof *n);
//     n->type  = type;
//     n->left  = l;
//     n->right = r;
//     return (n);
// }

// int main(void)
// {
//     /* build “echo a b” */
//     t_argnode *args1 = argnode("a", true);
//     args1->next = argnode("b", true);
//     t_ast *echo = cmd_node("echo", args1);

//     /* build “grep b” */
//     t_argnode *args2 = argnode("b", true);
//     t_ast *grep = cmd_node("grep", args2);

//     /* echo a b | grep b */
//     t_ast *pipe = op_node(N_PIPE, echo, grep);

//     /* build “ls” */
//     t_ast *ls = cmd_node("ls", NULL);

//     /* (echo a b | grep b) && ls */
//     t_ast *root = op_node(N_AND, pipe, ls);

//     /* and finally visualize it */
//     visualize_tree(root);

//     return (0);
// }
