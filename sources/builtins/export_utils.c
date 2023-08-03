/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:14:14 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/02 14:05:45 by wmoughar         ###   ########.fr       */
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
		if (ft_update_or_add_env_variable(env[i],
				env_list, NULL, NULL) == __system_call_error)
			return (__system_call_error);
		i++;
	}
	return (__success);
}

int	store_var_in_node(t_list **env_list, char *name,
	char *value, char *equal_sign)
{
	t_list	*new_node;
	t_env	*env_variable;

	env_variable = ft_calloc(1, sizeof(t_env));
	if (!env_variable)
		return (perror("error creating env_variable"), __system_call_error);
	new_node = ft_lstnew((void *)env_variable);
	if (!new_node)
		return (free(env_variable),
			perror("error creating new_node for env_variable"),
			__system_call_error);
	ft_assign(env_variable,
		name, value, equal_sign);
	ft_lstadd_front(env_list, new_node);
	return (__success);
}

int	ft_create_name_and_value(char *argument, char **name,
	char **value, char *equal_sign)
{
	int		value_len;

	if (!equal_sign)
	{
		*name = ft_strdup(argument);
		if (!*name)
			return (perror("error creating name in store_env"),
				__system_call_error);
		return (__success);
	}
	else
	{
		*name = ft_substr(argument, 0, equal_sign - argument);
		if (!*name)
			return (perror("error creating name in store_env"),
				__system_call_error);
	}
	value_len = ft_strlen(equal_sign + 1);
	if (value_len > 0)
		ft_substr_value(value, name, equal_sign, value_len);
	return (__success);
}

//argument with or without equal sign as input
bool	ft_is_syntax_error_in_env_name(char *string)
{
	bool	syntax_error;
	int		i;

	syntax_error = false;
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

void	ft_assign(t_env *env_variable,
	char *name, char *value, char *equal_sign)
{
	if (name)
	{
		ft_free_pointer_and_set_to_null((void **)&env_variable->name);
		env_variable->name = name;
	}
	ft_free_pointer_and_set_to_null((void **)&env_variable->value);
	env_variable->value = value;
	if (!env_variable->value && equal_sign)
		env_variable->print_empty_quotes = true;
	else
		env_variable->print_empty_quotes = false;
}
