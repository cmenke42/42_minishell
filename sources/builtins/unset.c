/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:30:47 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/26 22:13:25 by user             ###   ########.fr       */
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
		if (ft_is_syntax_error_in_env_name(arguments[i], false))
			return (__syntax_error);
		env_variable_to_remove = ft_search_for_env_variable(arguments[i], *env_list_new);
		if (env_variable_to_remove)
			ft_lstremove(env_list_new, env_variable_to_remove);
		i++;
	}
	return (__success);
}

void ft_lstremove(t_list **env_list_new, t_list *env_variable_to_remove)
{
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
