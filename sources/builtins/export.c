/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:56:03 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/04 21:19:52 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(char **arguemnts, t_list **env_list)
{
	int		i;
	int		status;
	bool	syntax_error;

	i = 0;
	syntax_error = false;
	while (arguemnts[++i])
	{
		if (!ft_strcmp(arguemnts[i], "_"))
			continue ;
		status = ft_update_or_add_env_variable(arguemnts[i],
				env_list, NULL, NULL);
		if (status == __syntax_error)
			syntax_error = true;
		else if (status)
			return (status);
	}
	if (i == 1)
	{
		if (print_export(env_list) == __system_call_error)
			return (__system_call_error);
	}
	if (syntax_error)
		return (__syntax_error);
	return (__success);
}

//only allocated memory for name && value
int	ft_update_or_add_env_variable(char *argument, t_list **env_list,
		char *name, char *value)
{
	t_list	*env_update;
	int		status;
	char	*equal_sign;

	status = __success;
	equal_sign = NULL;
	if (!name && !value)
	{
		status = name_value_status(&name, &value, equal_sign, argument);
		if (status)
			return (status);
	}
	else if (name && value)
		equal_sign = "";
	env_update = ft_search_for_env_variable(name, *env_list);
	if (env_update)
		ft_assign((t_env *)env_update->content, name, value, equal_sign);
	else if (!status)
		status = store_var_in_node(env_list, name, value, equal_sign);
	if (status)
	{
		ft_free_pointer_and_set_to_null((void **)&name);
		ft_free_pointer_and_set_to_null((void **)&value);
	}
	return (status);
}

int	name_value_status(char **name, char **value,
	char *equal_sign, char *argument)
{
	equal_sign = ft_strchr(argument, '=');
	if (ft_is_syntax_error_in_env_name(argument))
		return (__syntax_error);
	if (!ft_create_name_and_value(argument, name, value, equal_sign))
		return (__system_call_error);
	return (__success);
}
