// /* tree_visualizer.c */
#include "../parser.h"
// #include <math.h>

// #define MAX_LABEL 64
// #define HSP 6              // horizontal spacing between subtrees
// #define VSP 4              // vertical spacing per generation
// #define LEFT_MARGIN "\t\t" // 10 spaces

// /* 1) Compute tree depth */
// static int	tree_depth(t_ast *n)
// {
// 	int	ld;
// 	int	rd;

// 	if (!n)
// 		return (0);
// 	ld = tree_depth(n->left);
// 	rd = tree_depth(n->right);
// 	return (1 + (ld > rd ? ld : rd));
// }

// /* 2) Build the textual label for a node */
// static void	get_label(t_ast *n, char *buf, int buf_sz)
// {
// 	buf[0] = '\0';
// 	if (n->type == N_CMD)
// 	{
// 		/* command */
// 		if (n->cmd.command)
// 			strncat(buf, n->cmd.command, buf_sz - strlen(buf) - 1);
// 		/* options array */
// 		if (n->cmd.options)
// 		{
// 			for (int i = 0; n->cmd.options[i]; i++)
// 			{
// 				strncat(buf, " ", buf_sz - strlen(buf) - 1);
// 				strncat(buf, n->cmd.options[i], buf_sz - strlen(buf) - 1);
// 			}
// 		}
// 		/* arguments linked list */
// 		for (t_argnode *a = n->cmd.args; a; a = a->next)
// 		{
// 			strncat(buf, " ", buf_sz - strlen(buf) - 1);
// 			strncat(buf, a->value, buf_sz - strlen(buf) - 1);
// 		}
// 		/* redirections */
// 		for (t_redir *r = n->cmd.redirs; r; r = r->next)
// 		{
// 			if (r->op == T_REDIR_IN)
// 				strncat(buf, " <", buf_sz - strlen(buf) - 1);
// 			else if (r->op == T_REDIR_OUT)
// 				strncat(buf, " >", buf_sz - strlen(buf) - 1);
// 			else if (r->op == T_REDIR_APPEND)
// 				strncat(buf, " >>", buf_sz - strlen(buf) - 1);
// 			else /* T_REDIR_HERE */
// 				strncat(buf, " <<", buf_sz - strlen(buf) - 1);
// 			strncat(buf, r->target, buf_sz - strlen(buf) - 1);
// 		}
// 		if (buf[0] == '\0')
// 			strncpy(buf, "CMD()", buf_sz);
// 	}
// 	else if (n->type == N_PIPE)
// 		strncpy(buf, "PIPE", buf_sz);
// 	else if (n->type == N_AND)
// 		strncpy(buf, "AND", buf_sz);
// 	else /* N_OR */
// 		strncpy(buf, "OR", buf_sz);
// 	buf[buf_sz - 1] = '\0';
// }

// /* 3) Compute how wide a subtree must be */
// static int	subtree_width(t_ast *n)
// {
// 	char	lbl[MAX_LABEL];
// 	int		w;
// 	int		lw;
// 	int		rw;
// 	int		spread;

// 	if (!n)
// 		return (0);
// 	get_label(n, lbl, sizeof lbl);
// 	w = strlen(lbl);
// 	if (n->left || n->right)
// 	{
// 		lw = subtree_width(n->left);
// 		rw = subtree_width(n->right);
// 		spread = lw + HSP + rw;
// 		if (spread > w)
// 			w = spread;
// 	}
// 	return (w);
// }

// /* 4) Render into the canvas with diagonal “/” and “\” */
// static void	render_rec(t_ast *n, char **canvas, int row, int left, int right)
// {
// 	int		mid;
// 	char	lbl[MAX_LABEL];
// 	int		len;
// 	int		start;
// 	int		lw;
// 	int		cl;
// 	int		cr;
// 	int		cm;
// 	int		dc;
// 	int		r;
// 	int		off;
// 	int		c;
// 	int		rw;
// 	int		cl;
// 	int		cr;
// 	int		cm;
// 	int		dc;
// 	int		r;
// 	int		off;
// 	int		c;

// 	if (!n)
// 		return ;
// 	mid = (left + right) / 2;
// 	/* draw label centered at row,mid */
// 	get_label(n, lbl, sizeof lbl);
// 	len = strlen(lbl);
// 	start = mid - len / 2;
// 	if (start < left)
// 		start = left;
// 	if (start + len > right + 1)
// 		start = right + 1 - len;
// 	memcpy(&canvas[row][start], lbl, len);
// 	/* left subtree branch */
// 	if (n->left)
// 	{
// 		lw = subtree_width(n->left);
// 		cl = left;
// 		cr = left + lw - 1;
// 		cm = (cl + cr) / 2;
// 		dc = mid - cm;
// 		for (int i = 1; i <= VSP; ++i)
// 		{
// 			r = row + i;
// 			off = (int)round((double)dc * i / VSP);
// 			c = mid - off;
// 			if (c >= 0 && r < row + VSP + 1)
// 				canvas[r][c] = '/';
// 		}
// 		render_rec(n->left, canvas, row + VSP + 1, cl, cr);
// 	}
// 	/* right subtree branch */
// 	if (n->right)
// 	{
// 		rw = subtree_width(n->right);
// 		cl = right - rw + 1;
// 		cr = right;
// 		cm = (cl + cr) / 2;
// 		dc = cm - mid;
// 		for (int i = 1; i <= VSP; ++i)
// 		{
// 			r = row + i;
// 			off = (int)round((double)dc * i / VSP);
// 			c = mid + off;
// 			if (c < right + 1 && r < row + VSP + 1)
// 				canvas[r][c] = '\\';
// 		}
// 		render_rec(n->right, canvas, row + VSP + 1, cl, cr);
// 	}
// }

// /* 5) Public entry: build canvas, render, print */
void	visualize_tree(t_ast *root)
{
// 	int depth = tree_depth(root);
// 	if (depth == 0)
// 		return ;

// 	int rows = depth * (VSP + 1) - VSP;
// 	int cols = subtree_width(root);

// 	/* allocate & clear */
// 	char **canvas = malloc(rows * sizeof *canvas);
// 	for (int r = 0; r < rows; ++r)
// 	{
// 		canvas[r] = malloc(cols + 1);
// 		memset(canvas[r], ' ', cols);
// 		canvas[r][cols] = '\0';
// 	}

// 	/* render it */
// 	render_rec(root, canvas, 0, 0, cols - 1);

// 	/* print with left margin */
// 	putchar('\n');
// 	printf(LEFT_MARGIN "\n\n");
// 	for (int r = 0; r < rows; ++r)
// 		printf(LEFT_MARGIN "%s\n", canvas[r]);
// 	printf(LEFT_MARGIN "\n\n");

// 	/* we skip freeing the canvas for simplicity */
}