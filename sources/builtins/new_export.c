/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:14:14 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/26 18:35:56 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_store_env_in_list(char **env, t_list **env_list)
{
	int		i;

	if (!env)
		return (__success);
	i = 0;
	while (env[i])
	{
		if (ft_store_one_variable_in_node(env_list, env[i], true) == __system_call_error)
			return (__system_call_error);
		i++;
	}
	return (__success);
}

int	ft_store_one_variable_in_node(t_list **env_list, char *argument, bool first_import)
{
	t_list	*new_node;
	t_env	*env_variable;

	env_variable = ft_calloc(1, sizeof(t_env));
	if (!env_variable)
		return (perror("error creating env_variable"), __system_call_error);
	new_node = ft_lstnew((void *)env_variable);
	if (!new_node)
	{
		free(env_variable);
		return (perror("error creating new_node for env_variable"), __system_call_error);
	}
	if (ft_assign_values_to_env_variable_node(env_variable, argument, first_import))
	{
		free(env_variable);
		free(new_node);
		return (__system_call_error);
	}
	ft_lstadd_back(env_list, new_node);
	return (__success);
}

int	ft_assign_values_to_env_variable_node(t_env *env_variable, char *argument, bool first_import)
{
	char	*equal_sign;
	char	*name;
	char	*value;

	value = NULL;
	equal_sign = ft_strchr(argument, '=');
	if (ft_is_syntax_error_in_env_name(argument, equal_sign, first_import))
		return (__syntax_error);
	if (ft_create_name_and_value(argument, &name, &value, equal_sign) == __system_call_error)
		return (__system_call_error);
	ft_assig_name_and_value_to_env_variable(env_variable, name, value);
	return (__success);
}

int	ft_create_name_and_value(char *argument, char **name, char **value, char *equal_sign)
{
	int		value_len;

	if (!equal_sign)
	{
		*name = ft_strdup(argument);
		if (!*name)
			return (perror("error creating name in store_env"), __system_call_error);
	}
	else
	{
		*name = ft_substr(argument, 0, equal_sign - argument);
		if (!*name)
			return (perror("error creating name in store_env"), __system_call_error);
	}
	value_len = ft_strlen(equal_sign + 1);
	if (value_len > 0)
	{
		*value = ft_substr(equal_sign, 1, value_len);
		if (!*value)
		{
			free(name);
			return (perror("error creating value in store_env"), __system_call_error);
		}
	}
	return (__success);
}

bool	ft_is_syntax_error_in_env_name(char *string, char *equal_sign, bool first_import)
{
	if (first_import)
		return (false);
	if (*string != '_')
		ft_print_export_wrong_identifier(string);
	return (false);
}

void	ft_assig_name_and_value_to_env_variable(t_env *env_variable, char *name, char *value)
{
	env_variable->name = name;
	env_variable->value = value;
}

void	ft_print_export_wrong_identifier(char *argument)
{
	// bash: export: `=': not a valid identifier
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(argument, 2);
	ft_putendl_fd("'", 2);
}


// int	ft_export(char **args, )