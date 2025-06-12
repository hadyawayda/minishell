/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:37:55 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/12 23:00:34 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_redir(t_tokentype t)
{
	return (t == T_REDIR_IN || t == T_REDIR_OUT || t == T_REDIR_APPEND
		|| t == T_REDIR_HERE);
}

/*–– create a new t_argnode from a word token ––*/
t_argnode	*make_argnode(const char *val, bool exp)
{
	t_argnode	*an;

	an = malloc(sizeof * an);
	ft_memset(an, 0, sizeof * an);
	an->value = ft_strdup(val);
	an->expandable = exp;
	an->next = NULL;
	return (an);
}

/*–– append an argnode to the list ––*/
void	append_argnode(t_argnode **head, t_argnode **tail, t_argnode *an)
{
	if (!*head)
		*head = an;
	else
		(*tail)->next = an;
	*tail = an;
}

/*–– add an option string into the next free slot in node->cmd.options[] ––*/
void	add_option(t_ast *node, const char *opt)
{
	int	i;

	i = 0;
	while (node->cmd.options[i])
		i++;
	node->cmd.options[i] = ft_strdup(opt);
	node->cmd.options[i + 1] = NULL;
}

void	handle_word_token(t_ast *node, t_token *tok, t_argnode **args_head,
		t_argnode **args_tail)
{
	t_argnode	*an;

	if (tok == NULL || tok->value == NULL)
		return ;
	if (node->cmd.command == NULL)
		node->cmd.command = ft_strdup(tok->value);
	else if (tok->value[0] == '-' && !tok->is_quoted)
		add_option(node, tok->value);
	else
	{
		an = make_argnode(tok->value, !tok->is_quoted);
		append_argnode(args_head, args_tail, an);
	}
}
