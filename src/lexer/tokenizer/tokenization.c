/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 04:49:44 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/04 21:44:34 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	process_tokens(t_shell *shell, const char *input, t_token tokens[],
		t_tokenstate *st)
{
	while (input[st->i])
	{
		skip_whitespaces_and_flush(input, st, tokens);
		if (!input[st->i])
			break ;
		if (input[st->i] == '$')
			dollar_parser(shell, input, st);
		else if (input[st->i] == '\'' || input[st->i] == '"')
		{
			st->had_quotes = true;
			quote_parser(shell, input, st);
		}
		else if (is_operator_char(input[st->i]))
		{
			flush_current(tokens, st);
			operator_parser(input, tokens, st);
		}
		else
			word_parser(input, st);
	}
}

void	token_builder(t_shell *shell, const char *input, t_token tokens[])
{
	t_tokenstate	st;

	st.i = 0;
	st.j = 0;
	st.had_quotes = false;
	st.cur = ft_strdup("");
	process_tokens(shell, input, tokens, &st);
	flush_current(tokens, &st);
	free(st.cur);
	tokens[st.j].type = (t_tokentype)-1;
	tokens[st.j].value = NULL;
	tokens[st.j].quoted = false;
}

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != (t_tokentype)-1)
	{
		printf("%s", tokens[i].value);
		if (tokens[i + 1].type != (t_tokentype) - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}

t_token	*input_tokenizer(t_shell *shell, char *input)
{
	t_token	*tokens;

	tokens = malloc(sizeof(t_token) * ARG_MAX);
	if (!tokens)
		return (NULL);
	token_builder(shell, input, tokens);
	print_tokens(tokens);
	return (tokens);
}
