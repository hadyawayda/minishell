/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:21:22 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/03 17:56:18 by hawayda          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../lib/execution.h"

/*
** Build a NULL-terminated char*[] from shell->env:
** each element is "KEY=VALUE". Caller must free with free_argv().
*/
char    **build_envp(t_env *env)
{
  char    **envp;
  t_env   *tmp;
  int     count;
  int     i;
  char    *tmpstr;
  char    *pair;

  count = 0;
  tmp = env;
  while (tmp != NULL)
  {
      count++;
      tmp = tmp->next;
  }
  envp = malloc(sizeof(char *) * (count + 1));
  if (envp == NULL)
      return NULL;
  i = 0;
  tmp = env;
  while (tmp != NULL)
  {
      tmpstr = ft_strjoin(tmp->key, "=");
      pair = ft_strjoin(tmpstr, tmp->value);
      free(tmpstr);
      envp[i] = pair;
      i++;
      tmp = tmp->next;
  }
  envp[i] = NULL;
  return envp;
}
