/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:14:14 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/26 21:33:51 by cmenke           ###   ########.fr       */
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
	int		status;

	env_variable = ft_calloc(1, sizeof(t_env));
	if (!env_variable)
		return (perror("error creating env_variable"), __system_call_error);
	new_node = ft_lstnew((void *)env_variable);
	if (!new_node)
		return (free(env_variable), perror("error creating new_node for env_variable"), __system_call_error);
	status = ft_assign_values_to_env_variable_node(env_variable, argument, first_import);
	if (status == __syntax_error || status == __system_call_error)
		return (free(env_variable), free(new_node), status);
	ft_lstadd_front(env_list, new_node);
	return (__success);
}

int	ft_assign_values_to_env_variable_node(t_env *env_variable, char *argument, bool first_import)
{
	char	*equal_sign;
	char	*name;
	char	*value;

	value = NULL;
	equal_sign = ft_strchr(argument, '=');
	if (ft_is_syntax_error_in_env_name(argument, first_import))
		return (__syntax_error);
	if (ft_create_name_and_value(argument, &name, &value, equal_sign) == __system_call_error)
		return (__system_call_error);
	ft_assig_name_and_value_to_env_variable(env_variable, name, value, equal_sign);
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
		return (__success);
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
			return (free(*name), perror("error creating value in store_env"), __system_call_error);
	}
	return (__success);
}

bool	ft_is_syntax_error_in_env_name(char *string, bool first_import)
{
	bool	syntax_error;
	int		i;

	syntax_error = false;
	if (first_import)
		return (false);
	i = 0;
	if (!(ft_isalpha(string[i]) || string[i++] == '_'))
		syntax_error = true;
	else
	{
		while (!syntax_error && string[i] && string[i] != '=')
		{
			if (!(ft_isalnum(string[i]) || string[i] == '_'))
				syntax_error = true;
			i++;
		}
	}
	if (syntax_error)
		return (ft_print_export_wrong_identifier(string), true);
	return (false);
}

void	ft_assig_name_and_value_to_env_variable(t_env *env_variable, char *name, char *value, char *equal_sign)
{
	if (name)
		env_variable->name = name;
	else
		ft_free_pointer_and_set_to_null((void **)&env_variable->value);
	env_variable->value = value;
	if (!env_variable->value && equal_sign)
		env_variable->print_empty_quotes = true;
	else
		env_variable->print_empty_quotes = false;
}

void	ft_print_export_wrong_identifier(char *argument)
{
	// bash: export: `=': not a valid identifier
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(argument, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}


// int	ft_export(char **args, )