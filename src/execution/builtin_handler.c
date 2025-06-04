/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:17:56 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/03 17:17:57 by hawayda          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../lib/execution.h"

/*
** Define each builtin as a distinct enum value.
** The final value (BI_NONE) means “not a builtin”.
*/
/*
** Map a command name (string) to its t_builtin value.
** Return BI_NONE if the name does not match any builtin.
*/
t_builtin    get_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (BI_CD);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (BI_PWD);
	if (ft_strcmp(cmd, "echo") == 0)
		return (BI_ECHO);
	if (ft_strcmp(cmd, "env") == 0)
		return (BI_ENV);
	if (ft_strcmp(cmd, "export") == 0)
		return (BI_EXPORT);
	if (ft_strcmp(cmd, "unset") == 0)
		return (BI_UNSET);
	if (ft_strcmp(cmd, "exit") == 0)
		return (BI_EXIT);
	return (BI_NONE);
}
