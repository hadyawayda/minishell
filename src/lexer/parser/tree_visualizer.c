#include "../parser.h"
#include <locale.h>
#include <wchar.h>

#define MIN_GAP 3      // minimum columns between left/right subtrees
#define MAX_HEIGHT 128 // maximum lines in the tree

// 1) Compute how many columns this subtree needs
static int	subtree_width(t_ast *node)
{
		const char *s = (node->cmd.argv
				&& node->cmd.argv[0]) ? node->cmd.argv[0] : "(cmd)";
		wchar_t ws[64];
	int	w;
	int	lw;
	int	rw;

	if (!node)
		return (0);
	if (node->type == N_CMD)
	{
		// width = length of first argv or "(cmd)"
		mbstowcs(ws, s, 64);
		w = wcslen(ws);
		return (w < MIN_GAP ? MIN_GAP : w);
	}
	lw = subtree_width(node->left);
	rw = subtree_width(node->right);
	return (lw + MIN_GAP + rw);
}

// 2) Recursively lay out the tree into a wchar_t canvas
static void	render(t_ast *node, wchar_t **canvas, int line, int col, int width)
{
	wchar_t	label[64];
	int		lablen;
	int		start;
	int		lw;
	int		rw;
	int		mid;
	int		lx;
	int		rx;

	if (!node)
		return ;
	// 2a) draw this node’s label centered in [col..col+width)
	if (node->type == N_CMD)
	{
		mbstowcs(label, node->cmd.argv
			&& node->cmd.argv[0] ? node->cmd.argv[0] : "(cmd)", 64);
	}
	else if (node->type == N_PIPE)
	{
		wcscpy(label, L"|");
	}
	else if (node->type == N_AND)
	{
		wcscpy(label, L"&&");
	}
	else
	{ // N_OR
		wcscpy(label, L"||");
	}
	lablen = wcslen(label);
	start = col + (width - lablen) / 2;
	for (int i = 0; i < lablen; i++)
		canvas[line][start + i] = label[i];
	// 2b) if we have children, draw connectors and recurse
	if (node->left || node->right)
	{
		lw = subtree_width(node->left);
		rw = subtree_width(node->right);
		mid = col + width / 2;
		// vertical line down from the middle of this node
		canvas[line + 1][mid] = L'│';
		// left child branch
		if (node->left)
		{
			lx = col + lw / 2;
			canvas[line + 2][lx] = L'┌';
			for (int x = lx + 1; x < mid; x++)
				canvas[line + 2][x] = L'─';
			canvas[line + 3][lx] = L'│';
			render(node->left, canvas, line + 4, col, lw);
		}
		// right child branch
		if (node->right)
		{
			rx = col + lw + MIN_GAP + rw / 2;
			for (int x = mid + 1; x < rx; x++)
				canvas[line + 2][x] = L'─';
			canvas[line + 2][rx] = L'┐';
			canvas[line + 3][rx] = L'│';
			render(node->right, canvas, line + 4, col + lw + MIN_GAP, rw);
		}
	}
}

// 3) Public entry: build canvas, render, then print
void	visualize_tree(t_ast *root)
{
	setlocale(LC_CTYPE, "");

	int width = subtree_width(root);
	int height = MAX_HEIGHT;

	// allocate canvas[height][width+1]
	wchar_t **canvas = malloc(sizeof(wchar_t *) * height);
	for (int i = 0; i < height; i++)
	{
		canvas[i] = malloc(sizeof(wchar_t) * (width + 1));
		for (int j = 0; j < width; j++)
			canvas[i][j] = L' ';
		canvas[i][width] = L'\0';
	}

	// render the tree
	render(root, canvas, 0, 0, width);

	// print non-empty rows
	for (int i = 0; i < height; i++)
	{
		wchar_t *row = canvas[i];
		// check if row has any non-space
		int j = 0;
		while (row[j] == L' ' && j < width)
			j++;
		if (j == width)
			break ;
		wprintf(L"%ls\n", row);
	}

	// free canvas
	for (int i = 0; i < height; i++)
		free(canvas[i]);
	free(canvas);
}
