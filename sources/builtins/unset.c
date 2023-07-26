/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:30:47 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/26 18:54:50 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*remove_from_list(t_env *env, char *name)
{
	t_env	*current;
	t_env	*prev;

	if (!env)
		return (NULL);
	current = env;
	prev = NULL;
	if (current && !ft_strcmp(current->name, name))
	{
		env = current->next;
		free_env(current);
		return (env);
	}
	while (current && ft_strcmp(current->name, name))
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return (env);
	prev->next = current->next;
	free_env(current);
	return (env);
}

void    ft_unset(char **command, t_env *env)
{
    int i;

    i = 1;
    if (command[1])
    {
        while (command[i])
            remove_from_list(env, command[i++]);
    }
    else
        return ;
}