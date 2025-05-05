/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 23:16:33 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/05 00:40:23 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

char	*expand_line_heredoc(t_shell *shell, const char *line)
{
	t_tokenstate	st;

	st.i = 0;
	st.cur = ft_strdup("");
	st.had_quotes = false;
	while (line[st.i])
	{
		if (line[st.i] == '$')
			dollar_parser(shell, line, &st);
		else
			append_char_inplace(&st.cur, line[st.i], &st.i);
	}
	return (st.cur);
}

char	*read_heredoc(char *delim, int expand, t_shell *shell)
{
	char	*buf;
	size_t	len;
	char	*line;
	char	*text;
	size_t	chunk;
	char	*newbuf;
	size_t	k;
	size_t	m;

	buf = ft_strdup("");
	len = 0;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		if (expand)
			text = expand_line_heredoc(shell, line);
		else
			text = ft_strdup(line);
		free(line);
		chunk = ft_strlen(text) + 1;
		newbuf = malloc(len + chunk + 1);
		k = 0;
		while (k < len)
		{
			newbuf[k] = buf[k];
			k++;
		}
		m = 0;
		while (m < chunk - 1)
		{
			newbuf[k + m] = text[m];
			m++;
		}
		newbuf[k + m] = '\n';
		newbuf[k + m + 1] = '\0';
		free(buf);
		buf = newbuf;
		len += chunk;
		free(text);
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
	tokens[idx] = tokens[idx + 1];
}

void	collect_heredocs(t_shell *shell, t_token tokens[])
{
	int		i;
	char	*delim;
	int		expand;

	i = 0;
	while (tokens[i].type != (t_tokentype)-1)
	{
		if (tokens[i].type == T_REDIR_HERE)
		{
			if (tokens[i+1].type != T_WORD)
			{
					fprintf(stderr,
							"syntax error near unexpected token `%s`\n",
							tokens[i+1].value ? tokens[i+1].value : "newline");
					return;
			}
			delim = tokens[i + 1].value;
			expand = !tokens[i + 1].quoted;
			tokens[i].heredoc = read_heredoc(delim, expand, shell);
			shift_left(tokens, i + 1);
			free(delim);
			i++;
			continue ;
		}
		i++;
	}
}
