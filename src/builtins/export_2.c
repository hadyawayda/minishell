/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:58:48 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/05 11:59:00 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtins.h"  

void	sort_env(char **arr)
{
	size_t	i;
	int		swapped;
	char	*tmp;

	if (!arr)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (arr[i + 1])
		{
			if (cmp_key(arr[i], arr[i + 1]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}

void	print_env(char **arr)
{
	size_t	i;
	char	*eq;
	size_t	key_len;

	i = 0;
	while (arr[i])
	{
		eq = ft_strchr(arr[i], '=');
		if (eq)
			key_len = eq - arr[i];
		else
			key_len = ft_strlen(arr[i]);
		write(1, "export ", 7);
		write(1, arr[i], key_len);
		if (eq && eq[1])
		{
			write(1, "=\"", 2);
			write(1, eq + 1, ft_strlen(eq + 1));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}

int	process_export(char **args, char **envp)
{
	char	**copy;
	size_t	i;

	(void)envp;
	i = 1;
	while (args[i])
	{
		export_arg(args[i]);
		i++;
	}
	copy = duplicate_env();
	sort_env(copy);
	print_env(copy);
	free(copy);
	return (0);
}
