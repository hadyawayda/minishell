/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:34:35 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/04 23:01:41 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/parser.h"

int	check_left_operand(t_token tokens[], int i)
{
	if (i == 0)
		return (-1);
	if (tokens[i - 1].type != T_WORD && tokens[i - 1].type != T_RPAREN)
		return (-1);
	return (0);
}

int	check_right_operand(t_token tokens[], int i)
{
	t_token	*next;

	next = &tokens[i + 1];
	if (next->type == ((t_tokentype)-1))
	{
		printf("syntax error near unexpected token `newline`\n");
		return (-1);
	}
	if (next->type != T_WORD && next->type != T_LPAREN)
	{
		printf("syntax error near unexpected token `%s`\n", next->value);
		return (-1);
	}
	return (0);
}

int	check_operator_sequence(t_token tokens[])
{
	int	i;

	i = 0;
	while (tokens[i].type != ((t_tokentype)-1))
	{
		if (tokens[i].type == T_AND || tokens[i].type == T_OR
			|| tokens[i].type == T_PIPE)
		{
			if (check_left_operand(tokens, i) < 0)
			{
				printf("syntax error near unexpected token `%s`\n",
					tokens[i].value);
				return (-1);
			}
			if (check_right_operand(tokens, i) < 0)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	check_dollar_paren(t_token tokens[])
{
	int	i;

	i = 0;
	while (tokens[i].type != ((t_tokentype)-1))
	{
		if (tokens[i].type == T_WORD && strcmp(tokens[i].value, "$") == 0
			&& tokens[i + 1].type == T_LPAREN)
		{
			printf("subshell syntax is forbidden `$()`\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	check_leading_token(t_token tokens[])
{
	if (tokens[0].type == ((t_tokentype)-1))
		return (0);
	if (tokens[0].type != T_WORD && tokens[0].type != T_LPAREN
		&& tokens[0].type != T_REDIR_IN && tokens[0].type != T_REDIR_OUT
		&& tokens[0].type != T_REDIR_APPEND && tokens[0].type != T_REDIR_HERE)
	{
		if (tokens[0].value)
			printf("syntax error near unexpected token `%s`\n",
				tokens[0].value);
		else
			printf("syntax error near unexpected token `newline`\n");
		return (-1);
	}
	return (0);
}
