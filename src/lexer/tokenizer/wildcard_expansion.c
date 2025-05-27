/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:01:06 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/27 21:10:59 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"
#include <dirent.h>

/*
**  Prints every token.value, showing any WILD_UNEXPANDABLE bytes
**  as “\x1F” so you can see them in your terminal.
*/
void	debug_print_tokens(t_token tokens[])
{
	int		i;
	char	*val;

	i = 0;
	while (tokens[i].type != (t_tokentype)-1)
	{
		val = tokens[i].value;
		printf("token[%d]: '", i);
		while (val && *val)
		{
			if (*val == WILD_UNEXPANDABLE)
				printf("\\x%02x", (unsigned char)*val);
			else
				putchar(*val);
			val++;
		}
		printf("'\n");
		i++;
	}
}

/*
**  Return 1 if `val` contains a '*' not preceded by our unexpandable marker.
*/
int	need_expand(const char *val)
{
	int	i;

	i = 0;
	while (val[i])
	{
		if (val[i] == '*' && (i == 0 || val[i - 1] != WILD_UNEXPANDABLE))
			return (1);
		i++;
	}
	return (0);
}

/*
**  Remove all marker bytes so that a quoted "*" becomes a real '*' in the final
**  literal.
*/
void	strip_unexpandable(char *val)
{
	int	r;
	int	w;

	r = 0;
	w = 0;
	while (val[r])
	{
		if (val[r] == WILD_UNEXPANDABLE)
			r++;
		else
			val[w++] = val[r++];
	}
	val[w] = '\0';
}

/*
**  Build a cleaned pattern (a malloc'd string) where WILD_UNEXPANDABLE+'*'
**  becomes just '*' and real '*' remain.
*/
char	*clean_pattern(const char *pat)
{
	char	*out;
	int		i;

	out = ft_strdup("");
	i = 0;
	while (pat[i])
	{
		if (pat[i] == WILD_UNEXPANDABLE && pat[i + 1] == '*')
		{
			append_char_inplace(&out, '*', &(int){++i});
			i++;
		}
		else
		{
			append_char_inplace(&out, pat[i], &i);
		}
	}
	return (out);
}

int	match_simple(const char *name, const char *pattern)
{
	const char	*p = pattern;
	const char	*n = name;
	size_t		len;

	/* leading literal? */
	if (*p != '*')
	{
		len = strcspn(p, "*");
		if (strncmp(n, p, len) != 0)
			return (0);
		n += len;
		p += len;
	}
	/* for each “*literal” chunk, find it in `n` */
	while (*p)
	{
		/* skip the ‘*’ */
		if (*p == '*')
			p++;
		len = strcspn(p, "*");
		if (len == 0)
			break ;
		n = strstr(n, p);
		if (!n)
			return (0);
		n += len;
		p += len;
	}
	/* if pattern doesn’t end in ‘*’, ensure we’re at the end */
	if (pattern[strlen(pattern) - 1] != '*' && *(n) != '\0')
		return (0);
	return (1);
}

/*
**  Scans CWD for entries matching `pattern`.  Allocates *matches and
**  returns count; caller must free them.
*/
int	get_matches(const char *pattern, char ***matches_out)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*clean;
	char			**ms;
	int				count;

	clean = clean_pattern(pattern);
	dir = opendir(".");
	if (!dir)
		return (0);
	ms = NULL;
	count = 0;
	while ((ent = readdir(dir)))
	{
		if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
			continue ;
		/* dot-files only if pattern literal starts with '.' */
		if (ent->d_name[0] == '.' && clean[0] != '.')
			continue ;
		if (match_simple(ent->d_name, clean))
		{
			ms = realloc(ms, sizeof(*ms) * (count + 1));
			ms[count++] = ft_strdup(ent->d_name);
		}
	}
	closedir(dir);
	free(clean);
	*matches_out = ms;
	return (count);
}

/*
**  Shift all tokens[from..] right by `n` slots to make room.
*/
void	shift_tokens_right(t_token tokens[], int from, int n)
{
	int	end;

	end = 0;
	while (tokens[end].type != (t_tokentype)-1)
		end++;
	/* move the sentinel too */
	while (end >= from)
	{
		tokens[end + n] = tokens[end];
		end--;
	}
}

/*
**  Insert a new word-token at `pos` whose value is `s`.
*/
void	insert_token(t_token tokens[], int pos, const char *s)
{
	tokens[pos].type = T_WORD;
	tokens[pos].value = ft_strdup(s);
	tokens[pos].is_quoted = false;
	tokens[pos].heredoc = NULL;
	/* you can set is_expandable[pos] here if you track it */
}

/*
**  The main expansion loop.
*/
void	expand_wildcards(t_token tokens[])
{
	int		j;
	char	**matches;
	int		mcount;
	int		k;

	j = 0;
	while (tokens[j].type != (t_tokentype)-1)
	{
		if (need_expand(tokens[j].value))
		{
			mcount = get_matches(tokens[j].value, &matches);
			if (mcount > 0)
			{
				/* replace original */
				free(tokens[j].value);
				tokens[j].value = ft_strdup(matches[0]);
				/* insert the rest */
				if (mcount > 1)
				{
					shift_tokens_right(tokens, j + 1, mcount - 1);
					k = 1;
					while (k < mcount)
					{
						insert_token(tokens, j + k, matches[k]);
						k++;
					}
				}
				j += mcount;
			}
			else
			{
				/* no matches → literal, strip markers */
				strip_unexpandable(tokens[j].value);
				j++;
			}
			/* free matches array */
			k = 0;
			while (k < mcount)
				free(matches[k++]);
			free(matches);
		}
		else
			j++;
	}
}
