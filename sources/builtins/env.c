/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:06:49 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/26 18:28:35 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

t_env	*store_env(char **env)
{
	int		i;
	t_env	*env_list;
	t_env	*tail;
	t_env	*new_node;
	char	**split_result;
	
	env_list = NULL;
	tail = NULL;
	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		split_result = ft_split(env[i], '=');
		if (split_result && split_result[0] && split_result[1])
		{
			new_node = ft_create_node(split_result[0], split_result[1]);
			if (!new_node)
			{
				free_split(split_result);
				return (NULL);
			}
			if (!env_list)
			{
				env_list = new_node;
				tail = new_node;
			}
			else
			{
				tail->next = new_node;
				tail = tail->next;
			}
		}
		free_split(split_result);
		i++;
	}
	return (env_list);
}


void	print_env(t_env *envp)
{
	while (envp)
	{
		if (envp->name && envp->value)
			printf("%s=%s\n", envp->name, envp->value);
		envp = envp->next;
	}
}

