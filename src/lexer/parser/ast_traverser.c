/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_traverser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 02:43:35 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/28 23:17:44 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	traverse_ast(t_ast *n)
{
	// t_argnode	*arg;
	// int			idx;
	// t_redir		*r;
	// 			const char *op;

	// if (!n)
	// 	return ;
	// if (n->type == N_CMD)
	// {
	// 	/* Leaf: print the command itself */
	// 	printf("cmd: %s\n", n->cmd.command ? n->cmd.command : "(null)");
	// 	/* Options[] */
	// 	printf("options:");
	// 	if (n->cmd.options)
	// 	{
	// 		for (int i = 0; n->cmd.options[i]; i++)
	// 			printf(" %s", n->cmd.options[i]);
	// 	}
	// 	printf("\n");
	// 	/* Positional arguments (linked list) */
	// 	{
	// 		arg = n->cmd.args;
	// 		idx = 1;
	// 		while (arg)
	// 		{
	// 			printf("arg%d: %s (%s)\n", idx++, arg->value,
	// 				arg->expandable ? "expandable" : "literal");
	// 			arg = arg->next;
	// 		}
	// 	}
	// 	/* Redirections */
	// 	{
	// 		r = n->cmd.redirs;
	// 		while (r)
	// 		{
	// 			switch (r->op)
	// 			{
	// 			case T_REDIR_IN:
	// 				op = "<";
	// 				break ;
	// 			case T_REDIR_OUT:
	// 				op = ">";
	// 				break ;
	// 			case T_REDIR_APPEND:
	// 				op = ">>";
	// 				break ;
	// 			case T_REDIR_HERE:
	// 				op = "<<";
	// 				break ;
	// 			default:
	// 				op = "?";
	// 				break ;
	// 			}
	// 			printf("redir: %s %s\n", op, r->target);
	// 			r = r->next;
	// 		}
	// 	}
	// 	printf("\n");
	// }
	// else
	// {
	// 	/* Internal node: print its connector, then recurse */
	// 	if (n->type == N_PIPE)
	// 		puts("[PIPE]");
	// 	else if (n->type == N_AND)
	// 		puts("[AND]");
	// 	else
	// 		puts("[OR]");
	// 	traverse_ast(n->left);
	// 	traverse_ast(n->right);
	// }
}
