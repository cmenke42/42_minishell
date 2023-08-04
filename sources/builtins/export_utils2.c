/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:36:06 by wmoughar          #+#    #+#             */
/*   Updated: 2023/08/04 20:42:21 by cmenke           ###   ########.fr       */
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
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(argument, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}



int	ft_substr_value(char **value, char **name, char *equal_sign, int value_len)
{
	*value = ft_substr(equal_sign, 1, value_len);
	if (!*value)
		return (free(*name),
			perror("error creating value in store_env"),
			__system_call_error);
	return (__success);
}
