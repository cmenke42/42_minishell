/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:36:06 by wmoughar          #+#    #+#             */
/*   Updated: 2023/08/04 22:53:30 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_search_for_env_variable(char *variable_name, t_list *env_list)
{
	t_env	*one_env_variable;

	if (!variable_name || !env_list)
		return (NULL);
	while (env_list)
	{
		one_env_variable = (t_env *)env_list->content;
		if (!ft_strcmp(one_env_variable->name, variable_name))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	ft_print_export_wrong_identifier(char *argument)
{
	ft_put
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(argument, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

//argument with or without equal sign as input


void	ft_free_name_and_value(char **name, char **value)
{
	ft_free_pointer_and_set_to_null((void **)name);
	ft_free_pointer_and_set_to_null((void **)value);
}
