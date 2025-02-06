/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 03:16:33 by fel-ghaz          #+#    #+#             */
/*   Updated: 2024/09/27 01:34:59 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ma zabatit
// shou 3am tehke?
void	ft_cd(char *input)
{
	char	*current_directory;
	char	*new_directory;
	char	*pwd_env;

	current_directory = getenv("PWD");
	new_directory = NULL;
	pwd_env = NULL;
	if (current_directory == NULL)
	{
		ft_printf("Unable to get directory");
		return ;
	}
	if (input[0] == '/')
		ft_strcopy(new_directory, input);
	else
	{
		ft_strcopy(new_directory, current_directory);
		ft_strcat(new_directory, "/");
		ft_strcat(new_directory, input);
	}
	if (chdir(new_directory) != 0)
		ft_printf("errorr");
	else
	{
		ft_strcopy(pwd_env, "PWD=");
		ft_strcat(pwd_env, new_directory); // mazbut he l part??
	}
}
