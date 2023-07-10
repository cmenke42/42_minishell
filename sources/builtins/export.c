/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:55:14 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/09 16:45:36 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"
#include <string.h>

t_env	*add_to_list(t_env *env, char *var)
{
	t_env	*new;
	t_env	*tmp;
	char	**split;

	ft_check_name_start(var);
	new = malloc(sizeof(t_env));
	if (!ft_strchr(var, '='))
	{
		new->name = ft_strdup(var);
		new->value = NULL;
	}
	else
	{
		split = ft_split(var, '=');
		new->name = split[0];
		if (split[1])
			new->value = ft_strdup(split[1]);
		else
			new->value = "";
	}
	new->next = NULL;
	ft_check_name(new);
	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	if (ft_check_duplicate(tmp, tmp->name, new->name) == 1)
		find_and_replace(tmp, new);
	else
		tmp->next = new;
	return tmp;
}

t_env	*sort_env(t_env *env)
{
	char	*swap;
	t_env	*tmp;

	tmp = env;
	if (!env && !env->next)
		return (NULL);
	while (env->next)
	{
		if (env->name[0] > env->next->name[0])
		{
			swap = env->name;
			env->name = env->next->name;
			env->next->name = swap;
			env = tmp;
		}
		else
			env = env->next;
	}
	env = tmp;
	return (env);
}

void	export(t_env *env)
{
	t_env	*sorted_env;
	sorted_env = sort_env(env);
		if (!sorted_env)
		{
			printf("SORTED ENV IS NULL!\n");
			exit(1);
		}
	while (sorted_env)
	{
		if (sorted_env->name &&(ft_isalpha(sorted_env->name[0]) || sorted_env->name[0] == '_'))
			printf("declare -x ");
		if (sorted_env->name)
			printf("%s", sorted_env->name);
		if (sorted_env->value)
		{
			printf("=");
			printf("\"");
			if (sorted_env->value)
				printf("%s", sorted_env->value);
			printf("\"");
		}
		printf("\n");
		if (sorted_env->next)
		{
			sorted_env = sorted_env->next;
		}
		else
			break ;
	}
}