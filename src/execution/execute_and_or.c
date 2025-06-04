/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:17:58 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/04 22:17:06 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/execution.h"

/*
** For N_AND: if left returns 0, run right; else return left’s status.
*/
int	execute_and(t_shell *shell, t_ast *node)
{
	int	st;

	st = execute_ast(shell, node->left);
	if (st == 0)
		return (execute_ast(shell, node->right));
	return (st);
}

/*
** For N_OR: if left returns nonzero, run right; else return left’s status.
*/
int	execute_or(t_shell *shell, t_ast *node)
{
	int	st;

	st = execute_ast(shell, node->left);
	if (st != 0)
		return (execute_ast(shell, node->right));
	return (st);
}
