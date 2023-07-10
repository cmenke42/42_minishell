/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 14:08:54 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/09 16:45:57 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

t_env	*ft_create_node(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new)
	{
		new->name = ft_strdup(name);
		new->value = ft_strdup(value);
		new->next = NULL;
	}
	return (new);
}

void	ft_check_name(t_env *env)
{
	if ((ft_isalpha(env->name[0]) == 0 && env->name[0] != '_')) 
	{
		printf("bash: export: `%c': not a valid identifier\n",env->name[0]);
		exit(1);
	}
	int i = 1;
	while (env->name[i])
	{
		if (!ft_isalnum(env->name[i]))
		{
			printf("bash: export: `%s': not a valid identifier\n", env->name);
			exit(1);
		}
		i++;
	}
}

void	ft_check_name_start(char *s)
{
	if (s[0] == '=')
	{
		printf("bash: export: `%c': not a valid identifier\n",s[0]);
		exit(1);
	}
}

int	ft_check_duplicate(t_env *env, char *name, char *new_name)
{
	while (env)
	{
		if (ft_strncmp(name, new_name, ft_strlen(name)) == 0)
			return 1;
		env = env->next;
	}
	return 0;
}

t_env	*find_and_replace(t_env *env, t_env *new)
{
	while (env)
	{
		if (ft_strncmp(env->name, new->name, ft_strlen(env->name)) == 0)
			env->value = new->value;
		env = env->next;
	}
	return env;
}


