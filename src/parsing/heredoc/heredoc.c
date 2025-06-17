/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 23:16:33 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/17 03:24:01 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	process_hd_line(t_hd_state *st, char *line)
{
	size_t	chunk_len;
	char	*chunk;

	if (line == NULL)
	{
		if (g_last_signal == SIGINT)
		{
			free(st->buf);
			return (-1);
		}
		printf("-minishell: warning: here-document delimited "
			"by end-of-file (wanted `eof')\n");
		return (0);
	}
	if (ft_strcmp(line, st->delim) == 0)
		return (0);
	chunk = make_chunk(st->shell, line, st->expand, &chunk_len);
	st->buf = append_buf(st->buf, st->len, chunk, chunk_len);
	st->len += chunk_len;
	free(chunk);
	return (1);
}

char	*read_heredoc(char *delim, int expand, t_shell *shell)
{
	t_hd_state	st;
	char		*line;
	int			code;

	st.delim = delim;
	st.expand = expand;
	st.shell = shell;
	st.buf = ft_strdup("");
	st.len = 0;
	while (1)
	{
		line = readline("heredoc> ");
		code = process_hd_line(&st, line);
		free(line);
		if (code > 0)
			continue ;
		if (code < 0)
			return (NULL);
		break ;
	}
	return (st.buf);
}

void	shift_left(t_token tokens[], int idx)
{
	while (tokens[idx].type != (t_tokentype)-1)
	{
		tokens[idx] = tokens[idx + 1];
		idx++;
	}
}

int	process_heredoc_token(t_shell *shell, t_token tokens[], int i)
{
	char	*delim;
	int		expand;

	if (tokens[i + 1].type != T_WORD)
	{
		if (tokens[i + 1].value)
			printf("syntax error near unexpected token `%s`\n", tokens[i
				+ 1].value);
		else
			printf("syntax error near unexpected token `newline`\n");
		return (-1);
	}
	delim = tokens[i + 1].value;
	expand = !tokens[i + 1].is_quoted;
	tokens[i].heredoc = read_heredoc(delim, expand, shell);
	shift_left(tokens, i + 1);
	free(delim);
	return (i);
}

void	collect_heredocs(t_shell *shell, t_token tokens[])
{
	int	i;
	int	next_idx;

	i = 0;
	while (tokens[i].type != (t_tokentype)-1)
	{
		if (tokens[i].type == T_REDIR_HERE)
		{
			next_idx = process_heredoc_token(shell, tokens, i);
			if (next_idx < 0)
				return ;
			i = next_idx;
		}
		i++;
	}
}
