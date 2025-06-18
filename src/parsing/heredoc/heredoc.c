/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 23:16:33 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/18 02:03:34 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* read every byte from ‘fd’ into a growable buffer; return it and set *tot */
static char	*collect_heredoc_data(int fd, size_t *tot)
{
	char	tmp[4096];
	char	*buf;
	ssize_t	n;

	buf = NULL;
	*tot = 0;
	n = read(fd, tmp, sizeof(tmp));
	while (n > 0)
	{
		buf = append_chunk(&buf, tot, tmp, n);
		n = read(fd, tmp, sizeof(tmp));
	}
	return (buf);
}

char	*heredoc_parent(int fd[2], pid_t pid)
{
	char	*buf;
	size_t	tot;
	int		status;

	close(fd[1]);
	buf = collect_heredoc_data(fd[0], &tot);
	close(fd[0]);
	ignore_signals();
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFSIGNALED(status))
	{
		g_last_signal = WTERMSIG(status);
		free(buf);
		return ((char *)-1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		free(buf);
		return ((char *)-1);
	}
	if (buf)
		buf[tot] = '\0';
	else
		buf = ft_strdup("");
	return (buf);
}

int	process_heredoc_token(t_shell *shell, t_token tok[], int i)
{
	int		pfd[2];
	pid_t	pid;
	char	*buf;

	if (tok[i + 1].type != T_WORD || pipe(pfd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		close(pfd[0]);
		close(pfd[1]);
		return (-1);
	}
	if (pid == 0)
		heredoc_child(pfd, tok[i + 1].value, !tok[i + 1].is_quoted, shell);
	buf = heredoc_parent(pfd, pid);
	if (buf == (char *)-1)
		return (-1);
	if (buf == NULL)
		buf = ft_strdup("");
	tok[i].heredoc = buf;
	free(tok[i + 1].value);
	shift_left(tok, i + 1);
	return (i);
}

/* return the index of the next unprocessed heredoc operator, or -1 */
static int	find_next_heredoc(t_token tok[])
{
	int	i;

	i = 0;
	while (tok[i].type != (t_tokentype)-1)
	{
		if (tok[i].type == T_REDIR_HERE && tok[i].heredoc == NULL)
			return (i);
		i++;
	}
	return (-1);
}

/*
 * Loop: find one heredoc token, spawn child to read it, shift it out,
 * then repeat until there are no more << in the token list.
 * On Ctrl-D (EOF) read_heredoc returns an empty string and we move on.
 * On Ctrl-C (SIGINT) process_heredoc_token returns <0 and we abort.
 */
int	collect_heredocs(t_shell *shell, t_token tok[])
{
	int	idx;

	idx = find_next_heredoc(tok);
	while (idx >= 0)
	{
		ignore_signals();
		idx = process_heredoc_token(shell, tok, idx);
		setup_signals();
		if (idx < 0)
			return (-1);
		idx = find_next_heredoc(tok);
	}
	return (0);
}
