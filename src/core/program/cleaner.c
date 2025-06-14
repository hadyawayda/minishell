/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:43:22 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/13 00:04:13 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/core.h"

void	free_shell(t_shell *shell)
{
	if (shell)
	{
		free_env(shell->env);
		free(shell);
	}
}
