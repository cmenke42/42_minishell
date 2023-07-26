/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:30:47 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/26 20:55:25 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(char **arguments, t_list **env_list_new)
{
	t_list	*env_variable_to_remove;
	int		i;

	i = 1;
	if (!*env_list_new)
		return (__success);
	while (arguments[i])
	{
		//syntax check
		if (ft_search_for_env_variable(arguments[i], *env_list_new, &env_variable_to_remove) == __system_call_error)
			return (__system_call_error);
		if (env_variable_to_remove)
			ft_lstremove(env_list_new, env_variable_to_remove);
		i++;
	}
	return (__success);
}

void ft_lstremove(t_list **env_list_new, t_list *env_variable_to_remove)
{
	t_list *current;
	t_list *prev;

	if (!env_variable_to_remove)
		return ;
	prev = *env_list_new;
	if (env_variable_to_remove == *env_list_new)
		*env_list_new = env_variable_to_remove->next;
	else
	{
		while (prev->next != env_variable_to_remove)
			prev = prev->next;
		prev->next = env_variable_to_remove->next;
	}
	ft_lstdelone(env_variable_to_remove, ft_clear_env_variable);
}







// t_env	*remove_from_list(t_env *env, char *name)
// {
// 	t_env	*current;
// 	t_env	*prev;

// 	if (!env)
// 		return (NULL);
// 	current = env;
// 	prev = NULL;
// 	if (current && !ft_strcmp(current->name, name))
// 	{
// 		env = current->next;
// 		free_env(current);
// 		return (env);
// 	}
// 	while (current && ft_strcmp(current->name, name))
// 	{
// 		prev = current;
// 		current = current->next;
// 	}
// 	if (!current)
// 		return (env);
// 	prev->next = current->next;
// 	free_env(current);
// 	return (env);
// }

// void    ft_unset(char **command, t_env *env)
// {
//     int i;

//     i = 1;
//     if (command[1])
//     {
//         while (command[i])
//             remove_from_list(env, command[i++]);
//     }
//     else
//         return ;
// }