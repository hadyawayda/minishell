/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_matcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:28:34 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/27 21:34:38 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

/*
**  Consume a [...] class at *pp and advance both *sp and *pp.
**  Returns 1 on class‐match; 0 otherwise.
*/
int	match_bracket(const char **sp, const char **pp)
{
	int			neg;
	int			matched;
	const char	*p;
	char		c;

	p = *pp + 1;
	neg = 0;
	matched = 0;
	if (*p == '!' || *p == '^')
	{
		neg = 1;
		p++;
	}
	while (*p && *p != ']')
	{
		if (p[1] == '-' && p[2] && p[2] != ']')
		{
			if (**sp >= *p && **sp <= p[2])
				matched = 1;
			p += 3;
		}
		else
		{
			if (**sp == *p)
				matched = 1;
			p++;
		}
	}
	if (*p != ']')
		return (0);
	if ((matched && !neg) || (!matched && neg))
	{
		(*sp)++;
		*pp = p + 1;
		return (1);
	}
	return (0);
}

/*
**  Recursive, full‐featured glob matcher.
*/
int	match_pattern(const char *sp, const char *pp)
{
	if (!*pp)
		return (!*sp);
	if (*pp == '*')
	{
		/* skip consecutive '*' */
		while (pp[1] == '*')
			pp++;
		/* try to match zero or more chars */
		return (match_pattern(sp, pp + 1) || (*sp && match_pattern(sp + 1,
					pp)));
	}
	if (*pp == '?')
	{
		if (!*sp)
			return (0);
		return (match_pattern(sp + 1, pp + 1));
	}
	if (*pp == '[')
	{
		if (match_bracket(&sp, &pp))
			return (match_pattern(sp, pp));
		return (0);
	}
	if (*sp && *pp == *sp)
		return (match_pattern(sp + 1, pp + 1));
	return (0);
}

/*
**  Scan CWD for matches to the (possibly cleaned) pattern.
**  Caller must free(*matches_out)[i] and *matches_out itself.
*/
int	get_matches(const char *pattern, char ***matches_out)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*pat;
	char			**ms;
	int				count;
	int				i;

	pat = clean_pattern(pattern);
	dir = opendir(".");
	if (!dir)
	{
		free(pat);
		return (0);
	}
	ms = NULL;
	count = 0;
	while ((ent = readdir(dir)))
	{
		if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
			continue ;
		/* leading-dot rule */
		if (ent->d_name[0] == '.' && pat[0] != '.')
			continue ;
		if (match_pattern(ent->d_name, pat))
		{
			ms = realloc(ms, sizeof(*ms) * (count + 1));
			ms[count++] = ft_strdup(ent->d_name);
		}
	}
	closedir(dir);
	free(pat);
	*matches_out = ms;
	return (count);
}
