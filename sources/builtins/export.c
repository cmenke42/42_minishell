/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:55:14 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/03 17:20:50 by wmoughar         ###   ########.fr       */
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

t_env	*sort_env(t_env *envp)
{
	t_env	*sorted_list;
	t_env	*current;
	t_env	*temp;
	sorted_list = NULL;
	while (envp)
	{
		
		current = envp;
		envp = envp->next;
		if (sorted_list == NULL || strcmp(current->name,
			sorted_list->name) < 0)
		{
			current->next = sorted_list;
			sorted_list = current;
		}
		else
		{
			temp = sorted_list;
			while (temp->next != NULL && strcmp(current->name,
					temp->next->name) > 0)
			{	
				if (temp->next)
					temp = temp->next;
			}					
			current->next = temp->next;
			temp->next = current;
		}
	}
	return (sorted_list);
}

void	export(t_env *env)
{
	t_env	*sorted_env;
	sorted_env = sort_env(env);
	while (sorted_env)
	{
		if (ft_isalpha(sorted_env->name[0]) || sorted_env->name[0] == '_')
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
			sorted_env = sorted_env->next;
		else
			break ;
	}
}