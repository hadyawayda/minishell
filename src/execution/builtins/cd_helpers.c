/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:53:10 by nabbas            #+#    #+#             */
/*   Updated: 2025/06/20 21:26:02 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	fill_ptr(char **ptr, char *buf, pid_t *pid)
{
	*ptr = buf;
	while (**ptr != ' ' && **ptr != '\0')
		(*ptr)++;
	**ptr = '\0';
	*pid = ft_atoi(buf);
}

pid_t	get_pid(void)
{
	pid_t	pid;
	int		fd;
	char	buf[1024];
	char	*ptr;
	ssize_t	bytes_read;

	pid = -1;
	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (pid);
	}
	bytes_read = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (bytes_read < 0)
	{
		perror("read");
		return (pid);
	}
	buf[bytes_read] = '\0';
	fill_ptr(&ptr, buf, &pid);
	pid = ft_atoi(ptr);
	return (pid);
}

/* ---------- "$VAR not set" error ---------------------------- */
int	cd_env_error(char *var)
{
	printf("%s", "minishell: cd: ");
	printf("%s", var);
	printf("%s", " not set\n");
	return (1);
}

/* ---------- generic getcwd() failure reporter --------------- */
int	print_getcwd_error(char *cmd)
{
	char	*msg1;
	char	*msg2;

	msg1 = ": error retrieving current directory: getcwd: cannot "
		"access parent directories: ";
	msg2 = "No such file or directory\n";
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg1, 2);
	ft_putstr_fd(msg2, 2);
	return (1);
}

/* ----- duplicate $VAR into *target, set dash when needed ----- */
int	set_target_from_env(char **target, char *var, int *dash, t_env *env)
{
	char	*val;

	val = get_env_value(env, (char *)var);
	if (!val || val[0] == '\0')
		return (cd_env_error((char *)var));
	if (dash)
		*dash = 1;
	*target = ft_strdup(val);
	return (*target == NULL);
}
