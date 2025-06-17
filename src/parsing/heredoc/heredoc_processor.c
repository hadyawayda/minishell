/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:31:34 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/17 18:31:34 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	close_fds(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
	return (-1);
}

char	*append_chunk(char **buf, size_t *tot, char *tmp, ssize_t n)
{
	char	*new;
	size_t	i;

	new = ft_realloc(*buf, *tot + n + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < (size_t)n)
	{
		new[*tot + i] = tmp[i];
		i++;
	}
	*tot += n;
	return (new);
}

void	shift_left(t_token tok[], int idx)
{
	while (tok[idx].type != (t_tokentype)-1)
	{
		tok[idx] = tok[idx + 1];
		idx++;
	}
}

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
