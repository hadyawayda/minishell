/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:34:35 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/22 19:58:25 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

#define END_TOKEN ((t_tokentype)-1)

int	check_operator_sequence(t_token tokens[])
{
	t_token	*t;

	for (int i = 0; tokens[i].type != END_TOKEN; i++)
	{
		t = &tokens[i];
		if (t->type == T_AND || t->type == T_OR || t->type == T_PIPE)
		{
			if (i == 0 || (tokens[i - 1].type != T_WORD && tokens[i
					- 1].type != T_RPAREN))
			{
				fprintf(stderr, "syntax error near unexpected token `%s`\n",
					t->value);
				return (-1);
			}
			if (tokens[i + 1].type == END_TOKEN || (tokens[i + 1].type != T_WORD
					&& tokens[i + 1].type != T_LPAREN))
			{
				fprintf(stderr, "syntax error near unexpected token `%s`\n",
					tokens[i + 1].value ? tokens[i + 1].value : "newline");
				return (-1);
			}
		}
	}
	return (0);
}

int	check_dollar_paren(t_token tokens[])
{
	for (int i = 0; tokens[i].type != END_TOKEN; i++)
	{
		if (tokens[i].type == T_WORD && strcmp(tokens[i].value, "$") == 0
			&& tokens[i + 1].type == T_LPAREN)
		{
			fprintf(stderr, "subshell syntax is forbidden `$()`\n");
			return (-1);
		}
	}
	return (0);
}
