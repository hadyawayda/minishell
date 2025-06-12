/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 23:16:33 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/12 23:00:34 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*–– main heredoc reader ––*/
char	*read_heredoc(char *delim, int expand, t_shell *shell)
{
	char	*buf;
	size_t	len;
	char	*line;
	char	*chunk;
	size_t	chunk_len;

	buf = ft_strdup("");
	len = 0;
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		chunk = make_chunk(shell, line, expand, &chunk_len);
		free(line);
		buf = append_buf(buf, len, chunk, chunk_len);
		len += chunk_len;
		free(chunk);
	}
	return (buf);
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
