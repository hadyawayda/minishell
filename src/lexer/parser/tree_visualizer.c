/* tree_visualizer.c */
#include "../parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LABEL    64
#define HSP           6   // horizontal spacing between subtrees
#define VSP           4   // vertical spacing per generation
#define LEFT_MARGIN  "\t\t"  // 10 spaces

// 1) Compute tree depth
static int tree_depth(t_ast *n) {
	if (!n) return 0;
	int ld = tree_depth(n->left);
	int rd = tree_depth(n->right);
	return 1 + (ld > rd ? ld : rd);
}

// 2) Build label
static void get_label(t_ast *n, char *buf, int buf_sz) {
	if (n->type == N_CMD) {
		buf[0] = '\0';
		for (int i = 0; n->cmd.argv && n->cmd.argv[i]; ++i) {
			if (i) strncat(buf, " ", buf_sz - strlen(buf) - 1);
			strncat(buf, n->cmd.argv[i], buf_sz - strlen(buf) - 1);
		}
		if (buf[0]=='\0')
			strncpy(buf, "CMD()", buf_sz);
		for (t_redir *r = n->cmd.redirs; r; r = r->next) {
			if      (r->op == T_REDIR_IN)      strncat(buf, " <",  buf_sz - strlen(buf) - 1);
			else if (r->op == T_REDIR_OUT)     strncat(buf, " >",  buf_sz - strlen(buf) - 1);
			else if (r->op == T_REDIR_APPEND)  strncat(buf, " >>", buf_sz - strlen(buf) - 1);
			else if (r->op == T_REDIR_HERE)    strncat(buf, " <<", buf_sz - strlen(buf) - 1);
			strncat(buf, r->target, buf_sz - strlen(buf) - 1);
		}
	} else if (n->type == N_PIPE) {
		strncpy(buf, "PIPE", buf_sz);
	} else if (n->type == N_AND) {
		strncpy(buf, "AND", buf_sz);
	} else { // N_OR
		strncpy(buf, "OR", buf_sz);
	}
	buf[buf_sz-1] = '\0';
}

// 3) Compute subtree width
static int subtree_width(t_ast *n) {
	if (!n) return 0;
	char lbl[MAX_LABEL];
	get_label(n, lbl, sizeof lbl);
	int lw = strlen(lbl);
	int lw_l = subtree_width(n->left);
	int lw_r = subtree_width(n->right);
	if (n->left || n->right) {
		int spread = lw_l + HSP + lw_r;
		if (spread > lw) lw = spread;
	}
	return lw;
}

// 4) Render recursively, with smooth diagonals
static void render_rec(
	t_ast   *n,
	char   **canvas,
	int      row,
	int      left,
	int      right
) {
	if (!n) return;
	int mid = (left + right) / 2;

	// draw label
	char lbl[MAX_LABEL];
	get_label(n, lbl, sizeof lbl);
	int len = strlen(lbl);
	int start = mid - len/2;
	if (start < left)            start = left;
	if (start + len > right+1)   start = right + 1 - len;
	memcpy(&canvas[row][start], lbl, len);

	// left child
	if (n->left) {
		int lw = subtree_width(n->left);
		int cl = left;
		int cr = left + lw - 1;
		int cm = (cl + cr) / 2;
		int dc = mid - cm;
		for (int i = 1; i <= VSP; ++i) {
			int r = row + i;
			int offset = (int)round((double)dc * i / VSP);
			int c = mid - offset;
			if (c >= 0 && r < row + VSP + 1)
				canvas[r][c] = '/';
		}
		render_rec(n->left, canvas, row + VSP + 1, cl, cr);
	}

	// right child
	if (n->right) {
		int rw = subtree_width(n->right);
		int cl = right - rw + 1;
		int cr = right;
		int cm = (cl + cr) / 2;
		int dc = cm - mid;
		for (int i = 1; i <= VSP; ++i) {
			int r = row + i;
			int offset = (int)round((double)dc * i / VSP);
			int c = mid + offset;
			if (c < right+1 && r < row + VSP + 1)
				canvas[r][c] = '\\';
		}
		render_rec(n->right, canvas, row + VSP + 1, cl, cr);
	}
}

// 5) Build canvas, render, print with margin + trailing newline
void visualize_tree(t_ast *root) {
	int depth = tree_depth(root);
	if (!depth) return;
	int rows = depth * (VSP + 1) - VSP;
	int cols = subtree_width(root);

	// allocate & clear
	char **canvas = malloc(rows * sizeof *canvas);
	for (int r = 0; r < rows; ++r) {
		canvas[r] = malloc(cols + 1);
		memset(canvas[r], ' ', cols);
		canvas[r][cols] = '\0';
	}

	// render
	render_rec(root, canvas, 0, 0, cols - 1);
	putchar('\n');
	putchar('\n');

	 // --- print with fixed left margin, no per-line trimming ---
	for (int r = 0; r < rows; ++r) {
		printf(LEFT_MARGIN "%s\n", canvas[r]);
	}
	// one extra blank line at the end
	putchar('\n');
	putchar('\n');

	// (skip freeing for now)
}
