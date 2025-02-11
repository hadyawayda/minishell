/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 04:13:35 by fel-ghaz          #+#    #+#             */
/*   Updated: 2024/09/26 23:31:30 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\r');
}

int	is_separator(char *str, int i)
{
	char	*charset;
	int		j;

	charset = "|><\n";
	j = 0;
	while (charset[j])
	{
		if (str[i] == charset[j])
			return (1);
		j++;
	}
	return (0);
}

int	skip_spaces(char *str, int i)
{
	while (str[i] && check_space(str[i]))
		i++;
	return (i);
}

int	handle_quotes(char *str, int i, char *in_quote, int *handled)
{
	*handled = 0;
	if (str[i] == '\\' && str[i + 1])
	{
		i += 2;
		*handled = 1;
		return (i);
	}
	if (str[i] == '"' || str[i] == '\'')
	{
		if (*in_quote == 0)
			*in_quote = str[i++];
		else if (*in_quote == str[i])
		{
			*in_quote = 0;
			i++;
		}
		else
			i++;
		*handled = 1;
		return (i);
	}
	return (i);
}
char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	size_t	len;
	char	*dup;

	len = 0;
	while (s[len] && len < n)
		len++;
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
