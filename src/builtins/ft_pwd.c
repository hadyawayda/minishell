/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 03:04:17 by fel-ghaz          #+#    #+#             */
/*   Updated: 2024/09/27 01:35:17 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// shou na2is fiya cases?
// la2 akid mesh hal2ad z8ire
void	ft_pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_printf("%s\n", cwd);
		free(cwd);
	}
	else
		ft_printf("error getting cwd");
}