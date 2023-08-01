/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:30:47 by wmoughar          #+#    #+#             */
/*   Updated: 2023/08/01 21:19:26 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(char **arguments, t_list **env_list_new, t_shell_data *shell_data)
{
	t_list	*env_variable_to_remove;
	int		i;

	i = 1;
	if (!*env_list_new)
		return (__success);
	while (arguments[i])
	{
		if (ft_is_syntax_error_in_env_name(arguments[i]))
			return (__syntax_error);
		env_variable_to_remove = ft_search_for_env_variable(arguments[i],
				*env_list_new);
		if (env_variable_to_remove && !ft_strcmp(arguments[i], "PWD"))
			shell_data->print_quotes_for_oldpwd = true;
		if (env_variable_to_remove)
			ft_lstremove(env_list_new, env_variable_to_remove);
		i++;
	}
	return (__success);
}

void	ft_lstremove(t_list **env_list_new, t_list *env_variable_to_remove)
{
	t_list	*prev;

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
