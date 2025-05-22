/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:34:35 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/22 21:25:06 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	check_single_ampersand(t_token tokens[])
{
	int	i;

	i = 0;
	while (tokens[i].type != END_TOKEN)
	{
		if (tokens[i].type == T_WORD && strcmp(tokens[i].value, "&") == 0)
		{
			printf("syntax error: single '&' not allowed\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	check_redirection_sequence(t_token tokens[])
{
	t_tokentype	ty;
	int			i;

	i = 0;
	while (tokens[i].type != END_TOKEN)
	{
		ty = tokens[i].type;
		if (ty == T_REDIR_IN || ty == T_REDIR_OUT || ty == T_REDIR_APPEND
			|| ty == T_REDIR_HERE)
		{
			if (tokens[i + 1].type != T_WORD)
			{
				if (tokens[i + 1].value)
					printf("syntax error near unexpected token `%s`\n", tokens[i
						+ 1].value);
				else
					printf("syntax error near unexpected token `newline`\n");
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

int	check_parentheses_balance(t_token tokens[])
{
	int	depth;
	int	i;

	i = 0;
	depth = 0;
	while (tokens[i].type != END_TOKEN)
	{
		if (tokens[i].type == T_LPAREN)
			depth++;
		else if (tokens[i].type == T_RPAREN)
		{
			if (--depth < 0)
			{
				printf("syntax error: unmatched `)`\n");
				return (-1);
			}
		}
		i++;
	}
	if (depth > 0)
	{
		printf("syntax error: unmatched `(`\n");
		return (-1);
	}
	return (0);
}

int	check_trailing_token(t_token tokens[])
{
	int			i;
	t_tokentype	ty;

	i = 0;
	while (tokens[i].type != END_TOKEN)
		i++;
	if (i > 0)
		i--;
	ty = tokens[i].type;
	if (ty == T_AND || ty == T_OR || ty == T_PIPE || ty == T_REDIR_IN
		|| ty == T_REDIR_OUT || ty == T_REDIR_APPEND)
	{
		printf("syntax error near unexpected token `newline`\n");
		return (-1);
	}
	return (0);
}

int	check_syntax(t_token tokens[])
{
	if (check_leading_token(tokens) < 0)
		return (-1);
	if (check_single_ampersand(tokens) < 0)
		return (-1);
	if (check_operator_sequence(tokens) < 0)
		return (-1);
	if (check_redirection_sequence(tokens) < 0)
		return (-1);
	if (check_parentheses_balance(tokens) < 0)
		return (-1);
	if (check_dollar_paren(tokens) < 0)
		return (-1);
	if (check_trailing_token(tokens) < 0)
		return (-1);
	return (0);
}
