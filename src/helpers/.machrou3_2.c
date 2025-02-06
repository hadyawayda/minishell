/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .machrou3_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:21:50 by hawayda           #+#    #+#             */
/*   Updated: 2024/09/27 01:36:10 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	check_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\r');
}

int	is_separator(char *str, int i)
{
	char	*charset;
	int		j;

	charset = "|><;&\n";
	j = 0;
	while (charset[j])
	{
		if (str[i] == charset[j])
			return (1);
		j++;
	}
	return (0);
}

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && check_space(str[*i]))
		(*i)++;
}

char	*get_token(char *str, int *i)
{
	int		start;
	char	in_quote;
	char	*token;

	start = *i;
	in_quote = 0;
	while (str[*i])
	{
		if (str[*i] == '\\' && str[*i + 1])
		{
			(*i) += 2;
			continue ;
		}
		if ((str[*i] == '"' || str[*i] == '\''))
		{
			if (in_quote == 0)
				in_quote = str[(*i)++];
			else if (in_quote == str[*i])
			{
				in_quote = 0;
				(*i)++;
			}
			else
				(*i)++;
			continue ;
		}
		if (!in_quote && (check_space(str[*i]) || is_separator(str, *i)))
			break ;
		(*i)++;
	}
	token = strndup(&str[start], *i - start);
	return (token);
}

char	*get_separator(char *str, int *i)
{
	int		start;
	char	*token;

	start = *i;
	while (str[*i] && is_separator(str, *i))
		(*i)++;
	token = strndup(&str[start], *i - start);
	return (token);
}

char	**split(char *str)
{
	int		i;
	int		tokens_size;
	int		tokens_count;
	char	**tokens;
	char	*token;

	i = 0;
	tokens_size = 10;
	tokens_count = 0;
	tokens = malloc(tokens_size * sizeof(char *));
	if (!tokens)
		return (NULL);
	while (str[i])
	{
		skip_spaces(str, &i);
		if (!str[i])
			break ;
		if (is_separator(str, i))
		{
			token = get_separator(str, &i);
			tokens[tokens_count++] = token;
		}
		else
		{
			token = get_token(str, &i);
			tokens[tokens_count++] = token;
		}
		if (tokens_count >= tokens_size)
		{
			tokens_size *= 2;
			tokens = realloc(tokens, tokens_size * sizeof(char *));
			if (!tokens)
				return (NULL);
		}
	}
	tokens[tokens_count] = NULL;
	return (tokens);
}

/* Example usage:
int	main(void)
{
	char	**tokens;
	int		i;

	char *str = "echo >> file.tt | \\\"ju\\\"grep|a < b >> w > "
				"| a \"pa\"|\"|ttern\"";
	tokens = split(str);
	i = 0;
	if (!tokens)
	{
		ft_printf(stderr, "Memory allocation failed\n");
		return (1);
	}
	while (tokens[i])
	{
		ft_printf("Token %d: '%s'\n", i + 1, tokens[i]);
		free(tokens[i]);
		i++;
	}
	free(tokens);
	return (0);
}
*/
