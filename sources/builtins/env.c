/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:49:26 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/31 10:49:28 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_env_list(t_list *env_list)
{
	t_env	*env_variable;

	while (env_list)
	{
		env_variable = (t_env *)env_list->content;
		ft_print_one_env_variable(env_variable);
		env_list = env_list->next;
	}
}

void	ft_print_one_env_variable(t_env *env_variable)
{
	if (env_variable->name && env_variable->value)
		printf("%s=%s\n", env_variable->name, env_variable->value);
	else if (env_variable->name && env_variable->print_empty_quotes)
		printf("%s=\n", env_variable->name);
}
