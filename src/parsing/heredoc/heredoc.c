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

void	heredoc_child(int fd[2], char *delim, int expand, t_shell *sh)
{
	char	*txt;
	size_t	len;

	close(fd[0]);
	txt = read_heredoc(delim, expand, sh);
	if (!txt)
		_exit(1);
	len = ft_strlen(txt);
	write(fd[1], txt, len);
	free(txt);
	close(fd[1]);
	_exit(0);
}

char	*heredoc_parent(int fd[2], pid_t pid)
{
	char	tmp[4096];
	char	*buf;
	ssize_t	n;
	size_t	tot;

	buf = NULL;
	tot = 0;
	close(fd[1]);
	while ((n = read(fd[0], tmp, sizeof(tmp))) > 0)
		buf = append_chunk(&buf, &tot, tmp, n);
	close(fd[0]);
	waitpid(pid, NULL, 0);
	if (buf)
		buf[tot] = '\0';
	return (buf);
}

int	process_heredoc_token(t_shell *shell, t_token tok[], int i)
{
	int	pfd[2];
	pid_t	pid;
	char	*buf;

	if (tok[i + 1].type != T_WORD || pipe(pfd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (close_fds(pfd));
	if (pid == 0)
		heredoc_child(pfd, tok[i + 1].value,
			!tok[i + 1].is_quoted, shell);
	buf = heredoc_parent(pfd, pid);
	if (!buf)
		return (-1);
	tok[i].heredoc = buf;
	free(tok[i + 1].value);
	shift_left(tok, i + 1);
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
