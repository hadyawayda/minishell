/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:25:45 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/04 04:51:06 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	flush_current(t_token tokens[], t_tokenstate *st)
{
	if (st->cur[0] != '\0' || st->had_quotes)
	{
		tokens[st->j].type = T_WORD;
		tokens[st->j].value = ft_strdup(st->cur);
		tokens[st->j].quoted = st->had_quotes;
		st->j++;
		st->had_quotes = false;
		free(st->cur);
		st->cur = ft_strdup("");
	}
}

void	skip_whitespaces_and_flush(const char *input, t_tokenstate *st,
		t_token tokens[])
{
	while (input[st->i] && isspace((unsigned char)input[st->i]))
	{
		flush_current(tokens, st);
		st->i++;
	}
}

int	is_operator_char(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>' || c == '('
		|| c == ')');
}

void	free_tokens(char **tokens, int j)
{
	while (j > 0)
		free(tokens[--j]);
	free(tokens);
}

char	*append_char(char *s1, char c)
{
	char	*result;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}

void	append_char_inplace(char **dst, char c, int *i)
{
	char	*tmp;

	tmp = append_char(*dst, c);
	free(*dst);
	*dst = tmp;
	(*i)++;
}
