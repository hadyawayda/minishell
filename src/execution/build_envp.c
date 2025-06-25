/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:21:22 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/26 00:04:41 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
** Count how many entries are in the linked list `env`.
*/
static int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env;
	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

/*
** Given one t_env node, build a "KEY=VALUE" string.
** Caller must free the returned string.
*/
static char	*make_pair(t_env *entry)
{
	char	*tmpstr;
	char	*pair;

	tmpstr = ft_strjoin(entry->key, "=");
	pair = ft_strjoin(tmpstr, entry->value);
	free(tmpstr);
	return (pair);
}

/*
** Build a NULL-terminated char*[] from shell->env:
** each element is "KEY=VALUE". Caller must free with free_argv().
*/
char	**build_envp(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	int		total;
	int		i;

	total = count_env_vars(env);
	envp = malloc(sizeof(char *) * (total + 1));
	if (envp == NULL)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp != NULL)
	{
		envp[i] = make_pair(tmp);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

/*
 * If exec_path is a directory, print “<cmd>: Is a directory” and exit(126).
 * Otherwise return to the caller to go ahead and execve().
 */
void	check_directory_and_exit(char *exec_path, char **argv, char **envp)
{
	struct stat	st;

	if (ft_strchr(exec_path, '/') && stat(exec_path, &st) == 0)
	{
		if ((st.st_mode & 0xF000) == 0x4000)
		{
			ft_putstr_fd(argv[0], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			free(exec_path);
			if (envp)
				free_argv(envp);
			if (argv)
				free_argv(argv);
			exit(126);
		}
	}
}
