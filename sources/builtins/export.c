/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:56:03 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/01 21:20:58 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(char **arguemnts, t_list **env_list)
{
	int		i;
	int		status;
	bool	syntax_error;

	i = 0;
	status = __success;
	syntax_error = false;
	while (arguemnts[++i])
	{
		if (!ft_strcmp(arguemnts[i], "_"))
			continue ;
		status = ft_update_or_add_env_variable(arguemnts[i],
				env_list, NULL, NULL);
		if (status)
			return (status);
	}
	if (i == 1)
	{
		if (print_export(env_list) == __system_call_error)
			return (__system_call_error);
	}
	if (syntax_error)
		return (__syntax_error);
	return (status);
}

int	print_export(t_list **env_list)
{
	t_list	*sorted_env_list;
	t_list	*start_of_sorted_list;
	t_env	*one_env_variable;

	sorted_env_list = ft_lstmap(*env_list,
			ft_duplicate_env_variable, ft_clear_env_variable);
	if (!sorted_env_list)
		return (__system_call_error);
	sorted_env_list = ft_sort_list_asci(sorted_env_list);
	start_of_sorted_list = sorted_env_list;
	while (sorted_env_list)
	{
		one_env_variable = (t_env *)sorted_env_list->content;
		printf("declare -x %s", one_env_variable->name);
		if (one_env_variable->value)
			printf("=\"%s\"\n", one_env_variable->value);
		else if (one_env_variable->print_empty_quotes)
			printf("=\"\"\n");
		else
			printf("\n");
		sorted_env_list = sorted_env_list->next;
	}
	ft_lstclear(&start_of_sorted_list, ft_clear_env_variable);
	return (__success);
}

int	name_value_status(char **name, char **value,
	char *equal_sign, char *argument)
{
	int	status;

	status = __success;
	equal_sign = ft_strchr(argument, '=');
	if (ft_is_syntax_error_in_env_name(argument))
		status = __stop_execution;
	if (ft_create_name_and_value(argument,
			name, value, equal_sign) == __system_call_error)
		status = __system_call_error;
	return (status);
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

void	*ft_duplicate_env_variable(void *env_variable)
{
	t_env	*one_env_variable;
	t_env	*new_env_variable;

	one_env_variable = (t_env *)env_variable;
	new_env_variable = ft_calloc(1, sizeof(t_env));
	if (!new_env_variable)
		return (NULL);
	new_env_variable->name = ft_strdup(one_env_variable->name);
	if (one_env_variable->value)
		new_env_variable->value = ft_strdup(one_env_variable->value);
	else
		new_env_variable->value = NULL;
	new_env_variable->print_empty_quotes = one_env_variable->print_empty_quotes;
	if (!new_env_variable->name
		|| (one_env_variable->value && !new_env_variable->value))
		return (ft_clear_env_variable((void *)new_env_variable), NULL);
	return ((void *)new_env_variable);
}
