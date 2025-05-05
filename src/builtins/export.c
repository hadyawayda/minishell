/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:48:56 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/05 12:37:34 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>

int	is_valid_id(const char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	export_arg(char *arg)
{
	t_export_arg	st;

	st.eq = ft_strchr(arg, '=');
	if (st.eq)
	{
		st.key_len = st.eq - arg;
		st.key = ft_strndup(arg, st.key_len);
		st.val = st.eq + 1;
	}
	else
	{
		st.key = ft_strdup(arg);
		st.val = "";
	}
	if (st.key && is_valid_id(st.key))
		setenv(st.key, st.val, 1);
	else
	{
		write(2, "bash: export: ", 14);
		write(2, arg, ft_strlen(arg));
		write(2, ": not a valid identifier\n", 25);
	}
	free(st.key);
}

char	**duplicate_env(void)
{
	extern char	**environ;
	char		**copy;
	size_t		count;
	size_t		i;

	count = 0;
	while (environ[count])
		count++;
	copy = malloc((count + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = environ[i];
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

int	cmp_key(const char *a, const char *b)
{
	size_t	i;

	i = 0;
	while (a[i] && b[i] && a[i] != '=' && b[i] != '=' && a[i] == b[i])
		i++;
	if (((a[i] == '=') || !a[i]) && ((b[i] == '=') || !b[i]))
		return (0);
	if ((a[i] == '=') || !a[i])
		return (-1);
	if ((b[i] == '=') || !b[i])
		return (1);
	return ((unsigned char)a[i] - (unsigned char)b[i]);
}
