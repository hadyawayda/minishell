/* tree_visualizer.c */
#include "../parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LABEL  64
#define HSP         6   // horizontal spacing between subtrees
#define VSP         4   // vertical spacing per generation

// 1) Compute tree depth
static int tree_depth(t_ast *n) {
    if (!n) return 0;
    int ld = tree_depth(n->left);
    int rd = tree_depth(n->right);
    return 1 + (ld>rd ? ld : rd);
}

// 2) Build label: join argv into one string, or use PIPE/AND/OR
static void get_label(t_ast *n, char *buf, int buf_sz) {
    if (n->type == N_CMD) {
        buf[0] = '\0';
        for (int i = 0; n->cmd.argv && n->cmd.argv[i]; ++i) {
            if (i) strncat(buf, " ", buf_sz - strlen(buf) - 1);
            strncat(buf, n->cmd.argv[i], buf_sz - strlen(buf) - 1);
        }
        if (buf[0]=='\0')
            strncpy(buf, "CMD()", buf_sz);
    } else if (n->type == N_PIPE) {
        strncpy(buf, "PIPE", buf_sz);
    } else if (n->type == N_AND) {
        strncpy(buf, "AND", buf_sz);
    } else { // N_OR
        strncpy(buf, "OR", buf_sz);
    }
    buf[buf_sz-1] = '\0';
}

// 3) Compute how wide the subtree must be
static int subtree_width(t_ast *n) {
    if (!n) return 0;
    char lbl[MAX_LABEL];
    get_label(n, lbl, sizeof lbl);
    int lw = strlen(lbl);
    // for internal nodes, ensure at least left + HSP + right
    int left_w  = subtree_width(n->left);
    int right_w = subtree_width(n->right);
    if (n->left || n->right) {
        int spread = left_w + HSP + right_w;
        if (spread > lw) lw = spread;
    }
    return lw;
}

// 4) Render: place label at row; draw diagonal slashes of length VSP to each child
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
    if (start < left)        start = left;
    if (start + len > right+1) start = right+1 - len;
    memcpy(&canvas[row][start], lbl, len);

    // draw left branch: VSP slashes from (row+1, mid-1) down-left
    if (n->left) {
        int child_mid = (left + mid - HSP) / 2;
        int dc = mid - child_mid;
        for (int i = 1; i <= VSP; ++i) {
            int r = row + i;
            int c = mid - (i * dc + VSP/2) / VSP; 
            // simple linear interpolation towards child_mid
            if (c >= 0 && r < row + VSP + 1)
                canvas[r][c] = '/';
        }
        render_rec(n->left, canvas, row + VSP + 1, left, mid - HSP);
    }
    // draw right branch
    if (n->right) {
        int child_mid = (mid + HSP + right) / 2;
        int dc = child_mid - mid;
        for (int i = 1; i <= VSP; ++i) {
            int r = row + i;
            int c = mid + (i * dc + VSP/2) / VSP;
            if (c < right+1 && r < row + VSP + 1)
                canvas[r][c] = '\\';
        }
        render_rec(n->right, canvas, row + VSP + 1, mid + HSP, right);
    }
}

// 5) Public entry: build canvas, render, print
void visualize_tree(t_ast *root) {
    int depth = tree_depth(root);
    if (!depth) return;
    int rows = depth * (VSP + 1) - VSP;
    int cols = subtree_width(root);

    // allocate and clear
    char **canvas = malloc(rows * sizeof *canvas);
    for (int r = 0; r < rows; ++r) {
        canvas[r] = malloc(cols+1);
        memset(canvas[r], ' ', cols);
        canvas[r][cols] = '\0';
    }

    // draw and print
    render_rec(root, canvas, 0, 0, cols-1);
	putchar('\n');
    const int MARGIN = 4;
    for (int r = 0; r < rows; ++r) {
        int c = 0; while (c < cols && canvas[r][c] == ' ') ++c;
        if (c == cols) break;
        puts(canvas[r]);
    }
    // omit frees while tinkering
}
