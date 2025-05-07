/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:53:10 by nabbas            #+#    #+#             */
/*   Updated: 2025/05/07 13:10:22 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdlib.h>

/* ----- common "$VAR not set" error ----------------------------------- */
int	cd_env_error(char *var)
{
	write(2, "minishell: cd: ", 15);
	write(2, var, ft_strlen(var));
	write(2, " not set\n", 9);
	return (1);
}

/* ---- fetch $VAR, set *dash if given, duplicate into *target ----------- */
int	set_target_from_env(char **target, char *var, int *dash)
{
	char	*val;

	val = getenv(var);
	if (!val)
		return (cd_env_error(var));
	if (dash)
		*dash = 1;
	*target = ft_strdup(val);
	if (*target == NULL)
		return (1);
	return (0);
}
