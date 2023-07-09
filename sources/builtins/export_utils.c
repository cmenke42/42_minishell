/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 14:08:54 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/09 16:31:31 by wmoughar         ###   ########.fr       */
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

// t_env *add_to_list(t_env *head, char *var)
// {
// 	t_env *new_node;
// 	t_env *current;
// 	char **split_result = NULL;
	
// 	ft_check_name_start(var);
// 	new_node = malloc(sizeof(t_env));
// 	if (!ft_strchr(var, '='))
// 	{
// 		new_node->name = ft_strdup(var);
// 		new_node->value = NULL;
// 	}
// 	else
// 	{
// 		split_result = ft_split(var, '=');
// 		// if (ft_check_duplicate(new_node, split_result[0]))
// 		// {
// 		// 	find_and_replace(head, var);
// 		// 	new_node = new_node->next;
// 		// }
// 		//printf("\nHere\n")
// 		printf("%s\n", var);
		
// 			new_node->name = ft_strdup(split_result[0]);
		
// 			if (split_result[1] != NULL)
// 				new_node->value = ft_strdup(split_result[1]);
// 			else
// 				new_node->value = "";
// 			new_node->next = NULL;
// 			ft_check_name(new_node);
		
// 	}
// 	if (head == NULL)
// 		{
// 			head = new_node;
// 		}
// 		else
// 		{
// 			current = head;
// 			while (current->next)
// 			{
// 				current = current->next;
// 			}
// 			current->next = new_node;
// 		}
// 	return head;
// }

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
	{
		printf("OLD VALUE: %s\n", tmp->value);
		find_and_replace(tmp, new);
		printf("NEW VALUE: %s\n", tmp->value);
	}
	else
		tmp->next = new;
	env = tmp;
	return env;
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
		{
			//free(env->name);
			env->value = new->value;
		}
		env = env->next;
	}
	return env;
}


