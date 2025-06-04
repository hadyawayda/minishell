/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:18:18 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/04 21:59:52 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/execution.h"

/*
** Walk the t_redir linked list. For each redirect:
**   - open the target file (O_RDONLY, O_WRONLY|O_CREAT|O_TRUNC, or O_APPEND)
**   - dup2 into STDIN or STDOUT
**   - close the opened fd
*/

static int	open_or_exit(char *filename, int flags, int mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd < 0)
	{
		perror(filename);
		exit(1);
	}
	return (fd);
}

static void	redirect_in(char *target)
{
	int	fd;

	fd = open_or_exit(target, O_RDONLY, 0);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	redirect_out(char *target)
{
	int	fd;

	fd = open_or_exit(target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	redirect_append(char *target)
{
	int	fd;

	fd = open_or_exit(target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	apply_redirections(t_redir *redirs)
{
	int	pipefd[2];

	while (redirs != NULL)
	{
		if (redirs->op == T_REDIR_IN)
			redirect_in(redirs->target);
		else if (redirs->op == T_REDIR_OUT)
			redirect_out(redirs->target);
		else if (redirs->op == T_REDIR_APPEND)
			redirect_append(redirs->target);
		else if (redirs->op == T_REDIR_HERE)
		{
			if (pipe(pipefd) < 0)
			{
				perror("pipe");
				exit(1);
			}
			write(pipefd[1], redirs->target, ft_strlen(redirs->target));
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
		redirs = redirs->next;
	}
}
