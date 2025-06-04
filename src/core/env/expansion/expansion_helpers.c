/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 04:19:12 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/03 17:58:30 by hawayda          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

# include "../../../lib/core.h"

char	*get_env_value(t_env *env, char *key)
{
	if (!key || !env)
		return ("");
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			if (env->value)
				return (env->value);
			else
				return ("");
		}
		env = env->next;
	}
	return ("");
}
