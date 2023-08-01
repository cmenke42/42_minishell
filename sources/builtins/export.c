/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:56:03 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/01 12:11:19 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(char **arguemnts, t_list **env_list)
{
	int i;

	i = 0;
	while (arguemnts[++i])
	{
		if (!ft_strcmp(arguemnts[i], "_"))
			continue;
		if (ft_update_or_add_env_variable(arguemnts[i], env_list, NULL, NULL) == __system_call_error)
			return (__system_call_error);
	}
	if (i == 1)
	{
		if (print_export(env_list) == __system_call_error)
			return (__system_call_error);
	}
	return (__success);
}

int	print_export(t_list **env_list)
{
	t_list	*sorted_env_list;
	t_list 	*start_of_sorted_list;
	t_env	*one_env_variable;

	// if (!ft_search_for_env_variable("OLDPWD", *env_list))
	// 	if (ft_store_one_variable_in_node(env_list, "OLDPWD", false) == __system_call_error)
	// 		return (__system_call_error); ->its not happening inside bash, only at launch
	sorted_env_list = ft_lstmap(*env_list, ft_duplicate_env_variable, ft_clear_env_variable);
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

//only allocated memory for name && value
int	ft_update_or_add_env_variable(char *argument, t_list **env_list, char *name, char *value)
{
	t_list	*env_variable_to_update;
	int		status;
	char	*equal_sign;

	status = __success;
	equal_sign = NULL;
	//export add
	if (!name && !value)
	{
		equal_sign = ft_strchr(argument, '=');
		if (ft_is_syntax_error_in_env_name(argument))
			return (__stop_execution);
		if (ft_create_name_and_value(argument, &name, &value, equal_sign) == __system_call_error)
			return (__system_call_error);
	}
	//custom add
	else if (name && value)
		equal_sign = "";
	env_variable_to_update = ft_search_for_env_variable(name, *env_list);
	if (env_variable_to_update)
		ft_assign_name_and_value_to_env_variable((t_env *)env_variable_to_update->content, name, value, equal_sign);
	else if (!status)
		status = ft_store_one_variable_in_node(env_list, name, value, equal_sign);
	if (status)
	{
		ft_free_pointer_and_set_to_null((void **)&name);
		ft_free_pointer_and_set_to_null((void **)&value);
	}
	return (status);
}

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

t_list	*ft_sort_list_asci(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while(lst->next)
	{
		if (ft_strcmp(((t_env *)lst->content)->name, ((t_env *)lst->next->content)->name) > 0)
		{
			ft_swap(&lst->content, &lst->next->content);
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}

void	ft_swap(void **var1, void **var2)
{
	void	*swap;

	swap = *var1;
	*var1 = *var2;
	*var2 = swap;
}

void *ft_duplicate_env_variable(void *env_variable)
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
	if (!new_env_variable->name || (one_env_variable->value && !new_env_variable->value))
		return (ft_clear_env_variable((void *)new_env_variable), NULL);
	return ((void *)new_env_variable);
}
