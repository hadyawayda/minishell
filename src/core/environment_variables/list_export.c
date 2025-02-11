#include "../core.h"

int	count_env_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

t_env	**convert_env_to_array(t_env *env, int size)
{
	int		i;
	t_env	**array;

	array = (t_env **)malloc(sizeof(t_env *) * size);
	if (!array)
		return (NULL);
	i = 0;
	while (env)
	{
		array[i++] = env;
		env = env->next;
	}
	return (array);
}

int	compare_env(const void *a, const void *b)
{
	t_env	*env1;
	t_env	*env2;

	env1 = *(t_env **)a;
	env2 = *(t_env **)b;
	return (strcmp(env1->key, env2->key));
}

void	list_export(t_env *env)
{
	t_env	*sorted_env;

	sorted_env = env;
	sort_env_list(&sorted_env);
	while (sorted_env)
	{
		printf("declare -x %s", sorted_env->key);
		if (sorted_env->value)
			printf("=\"%s\"", sorted_env->value);
		printf("\n");
		sorted_env = sorted_env->next;
	}
}
