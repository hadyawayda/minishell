/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:33:27 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/12 23:23:49 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*expand_line_heredoc(t_shell *shell, const char *line)
{
	t_tokenstate	st;

	st.i = 0;
	st.cur = ft_strdup("");
	st.had_quotes = false;
	st.skip_expansion = false;
	while (line[st.i])
	{
		if (line[st.i] == '$')
			dollar_parser(shell, line, &st);
		else
			append_char_inplace(&st.cur, line[st.i], &st.i);
	}
	return (st.cur);
}

/*–– helper 1: build a “chunk” (line + newline) ––*/
char	*make_chunk(t_shell *shell, const char *line, int expand,
		size_t *chunk_len)
{
	char	*text;
	char	*chunk;
	size_t	tlen;
	size_t	i;

	if (expand)
		text = expand_line_heredoc(shell, line);
	else
		text = ft_strdup(line);
	tlen = ft_strlen(text);
	*chunk_len = tlen + 1;
	chunk = malloc(*chunk_len);
	i = 0;
	while (i < tlen)
	{
		chunk[i] = text[i];
		i++;
	}
	chunk[i] = '\n';
	free(text);
	return (chunk);
}

/*–– helper 2: append a chunk onto buf ––*/
char	*append_buf(char *buf, size_t len, const char *chunk, size_t chunk_len)
{
	char	*newbuf;
	size_t	i;
	size_t	j;

	newbuf = malloc(len + chunk_len + 1);
	i = 0;
	while (i < len)
	{
		newbuf[i] = buf[i];
		i++;
	}
	j = 0;
	while (j < chunk_len)
	{
		newbuf[i + j] = chunk[j];
		j++;
	}
	newbuf[i + j] = '\0';
	free(buf);
	return (newbuf);
}
