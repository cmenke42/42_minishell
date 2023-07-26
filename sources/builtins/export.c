/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:56:03 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/26 22:10:24 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(char **arguemnts, t_list **env_list)
{
	int i;

	i = 1;
	while (arguemnts[i])
	{
		if (ft_strcmp(arguemnts[i], "_") == 0)
			continue ;
		if (ft_update_or_add_env_variable(arguemnts[i], env_list) == __system_call_error)
			return (__system_call_error);
		i++;
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
	t_env	*one_env_variable;

	if (!ft_search_for_env_variable("OLDPWD", *env_list))
		if (ft_store_one_variable_in_node(env_list, "OLDPWD", false) == __system_call_error)
			return (__system_call_error);
	sorted_env_list = ft_sort_list_asci(*env_list);
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
	return (__success);
}

int	ft_update_or_add_env_variable(char *argument, t_list **env_list)
{
	t_list	*env_variable_to_update;
	int		status;

	status = __success;
	env_variable_to_update = ft_search_for_env_variable(argument, *env_list);
	if (env_variable_to_update)
		status = ft_assign_values_to_env_variable_node((t_env *)env_variable_to_update->content, argument, false);
	else if (!status)
		status = ft_store_one_variable_in_node(env_list, argument, false);
	return (status);
}

t_list	*ft_search_for_env_variable(char *argument, t_list *env_list)
{
	t_env	*one_env_variable;
	int		name_length;

	if (!argument || !env_list)
		return (NULL);
	ft_get_variable_name_lenght(argument, &name_length);
	while (env_list)
	{
		one_env_variable = (t_env *)env_list->content;
		if (!ft_strncmp(one_env_variable->name, argument, name_length))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	ft_get_variable_name_lenght(char *argument, int *name_length)
{
	char	*equal_sign;

	equal_sign = ft_strchr(argument, '=');
	if (equal_sign)
		*name_length = equal_sign - argument;
	else
		*name_length = ft_strlen(argument);
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