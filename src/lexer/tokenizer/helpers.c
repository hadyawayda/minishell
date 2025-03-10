/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:25:45 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/22 03:10:49 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

int	skip_whitespace(const char *input, int *i)
{
	int	skipped;

	skipped = 0;
	while (input[*i] == ' ' || input[*i] == '\t')
	{
		(*i)++;
		skipped = 1;
	}
	return (skipped);
}

int	is_operator_char(char c)
{
	if (c == '|' || c == '&' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	free_tokens(char **tokens, int j)
{
	while (j > 0)
		free(tokens[--j]);
	free(tokens);
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	*result;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}

char *append_char(char *s1, char c)
{
    char *result;
    size_t len;

    if (!s1)
        return (NULL);
    len = ft_strlen(s1);
    result = malloc(len + 2);
    if (!result)
        return (NULL);
    ft_strcpy(result, s1);
    result[len] = c;
    result[len + 1] = '\0';
    return (result);
}
