/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 04:49:44 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/04 22:51:36 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/lexer.h"

int	process_tokens(t_shell *shell, const char *input, t_token tokens[],
		t_tokenstate *st)
{
	while (input[st->i])
	{
		skip_whitespaces_and_flush(input, st, tokens);
		if (st->j > 0 && tokens[st->j - 1].type == T_REDIR_HERE)
			st->skip_expansion = true;
		if (!input[st->i])
			break ;
		if (input[st->i] == '$' && dollar_parser(shell, input, st) == -1)
			return (-1);
		else if (input[st->i] == '\'' || input[st->i] == '"')
		{
			st->had_quotes = true;
			if (quote_parser(shell, input, st) == -1)
				return (-1);
		}
		else if (is_operator_char(input[st->i]))
		{
			flush_current(tokens, st);
			operator_parser(input, tokens, st);
		}
		else
			word_parser(input, st);
	}
	return (0);
}

int	token_builder(t_shell *shell, const char *input, t_token tokens[])
{
	t_tokenstate	st;
	int				k;

	k = 0;
	st.i = 0;
	st.j = 0;
	st.had_quotes = false;
	st.cur = ft_strdup("");
	st.skip_expansion = false;
	if (process_tokens(shell, input, tokens, &st) == -1)
	{
		while (k < st.j)
			free(tokens[k++].value);
		free(st.cur);
		return (-1);
	}
	flush_current(tokens, &st);
	free(st.cur);
	tokens[st.j].type = (t_tokentype)-1;
	tokens[st.j].value = NULL;
	tokens[st.j].is_quoted = false;
	tokens[st.j].heredoc = NULL;
	return (0);
}

t_token	*input_tokenizer(t_shell *shell, char *input)
{
	t_token	*tokens;
	int		i;

	tokens = malloc(sizeof(t_token) * ARG_MAX);
	if (!tokens)
		return (NULL);
	i = 0;
	while (i < ARG_MAX)
	{
		tokens[i].type = (t_tokentype) - 1;
		tokens[i].value = NULL;
		tokens[i].is_quoted = false;
		tokens[i].heredoc = NULL;
		i++;
	}
	if (token_builder(shell, input, tokens) == -1)
	{
		free(tokens);
		return (NULL);
	}
	expand_wildcards(tokens);
	return (tokens);
}
