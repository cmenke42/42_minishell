/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:55:14 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/09 13:46:56 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"
#include <string.h>

// void	ft_name_error(char c)
// {
// 	printf("'%c' : Not a valid identifier", c);
// 	exit (1);
// }

// int	check_name(char *s)
// {
// 	if (ft_isalnum(s[0]) || s[0] == '_')
// 		return (1);
// 	else 
// 	{
// 		ft_name_error(s[0]);
// 		return (0);
// 	}
// }


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