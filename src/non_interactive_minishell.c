/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_interactive_minishell.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 03:40:29 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/20 03:51:46 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/core.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	non_interactive_minishell(av, envp);
	return (0);
}
