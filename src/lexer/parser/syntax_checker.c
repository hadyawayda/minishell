/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:34:35 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/04 18:56:11 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

#define END_TOKEN ((t_tokentype)-1)

// Forward declarations
static int	check_leading_token(t_token tokens[]);
static int	check_single_ampersand(t_token tokens[]);
static int	check_operator_sequence(t_token tokens[]);
static int	check_redirection_sequence(t_token tokens[]);
static int	check_parentheses_balance(t_token tokens[]);
static int	check_trailing_token(t_token tokens[]);

/**
 * Returns 0 if all checks pass, or -1 on the first syntax error.
 */
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
	if (check_trailing_token(tokens) < 0)
		return (-1);
	return (0);
}

// 1) First token must be a word or '('
static int	check_leading_token(t_token tokens[])
{
	if (tokens[0].type == END_TOKEN)
		return (0); // empty input is OK
	if (tokens[0].type != T_WORD && tokens[0].type != T_LPAREN)
	{
		fprintf(stderr, "syntax error near unexpected token `%s`\n",
			tokens[0].value ? tokens[0].value : "newline");
		return (-1);
	}
	return (0);
}

// 2) Ban any single '&' as a word token
static int	check_single_ampersand(t_token tokens[])
{
	for (int i = 0; tokens[i].type != END_TOKEN; i++)
	{
		if (tokens[i].type == T_WORD && strcmp(tokens[i].value, "&") == 0)
		{
			fprintf(stderr, "syntax error: single '&' not allowed\n");
			return (-1);
		}
	}
	return (0);
}

// 3) Logical (`&&`/`||`) and pipe (`|`) usage
static int	check_operator_sequence(t_token tokens[])
{
	t_token	*t;

	for (int i = 0; tokens[i].type != END_TOKEN; i++)
	{
		t = &tokens[i];
		if (t->type == T_AND      /* && */
			|| t->type == T_OR    /* || */
			|| t->type == T_PIPE) /* |  */
		{
			// cannot be first or follow a non-word/non-')'
			if (i == 0 || (tokens[i - 1].type != T_WORD && tokens[i
					- 1].type != T_RPAREN))
			{
				fprintf(stderr, "syntax error near unexpected token `%s`\n",
					t->value);
				return (-1);
			}
			// cannot be last or precede non-word/non-'('
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

// 4) Redirections (<, >, >>) must be followed by a word
static int	check_redirection_sequence(t_token tokens[])
{
	t_tokentype	ty;

	for (int i = 0; tokens[i].type != END_TOKEN; i++)
	{
		ty = tokens[i].type;
		if (ty == T_REDIR_IN || ty == T_REDIR_OUT || ty == T_REDIR_APPEND)
		{
			if (tokens[i + 1].type != T_WORD)
			{
				fprintf(stderr, "syntax error near unexpected token `%s`\n",
					tokens[i + 1].value ? tokens[i + 1].value : "newline");
				return (-1);
			}
		}
	}
	return (0);
}

// 5) Parentheses must be balanced
static int	check_parentheses_balance(t_token tokens[])
{
	int	depth;

	depth = 0;
	for (int i = 0; tokens[i].type != END_TOKEN; i++)
	{
		if (tokens[i].type == T_LPAREN)
			depth++;
		else if (tokens[i].type == T_RPAREN)
		{
			if (--depth < 0)
			{
				fprintf(stderr, "syntax error: unmatched `)`\n");
				return (-1);
			}
		}
	}
	if (depth > 0)
	{
		fprintf(stderr, "syntax error: unmatched `(`\n");
		return (-1);
	}
	return (0);
}

// 6) Last token cannot be an operator or redirection
static int	check_trailing_token(t_token tokens[])
{
	int			i;
	t_tokentype	ty;

	i = 0;
	while (tokens[i].type != END_TOKEN)
		i++;
	// step back to the last real token
	if (i > 0)
		i--;
	ty = tokens[i].type;
	if (ty == T_AND || ty == T_OR || ty == T_PIPE || ty == T_REDIR_IN
		|| ty == T_REDIR_OUT || ty == T_REDIR_APPEND)
	{
		fprintf(stderr, "syntax error near unexpected token `newline`\n");
		return (-1);
	}
	return (0);
}
