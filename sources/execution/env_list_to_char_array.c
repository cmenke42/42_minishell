/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_char_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:43:42 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/22 20:58:29 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_env_list_to_envp_array(t_shell_data *shell_data)
{
	t_env	*env_list;
	int		number_of_env_variables;

	env_list = shell_data->env_list;
	number_of_env_variables = ft_get_number_of_env_variables(env_list);
	shell_data->envp_array = ft_calloc(number_of_env_variables + 1, sizeof(char *));
	if (!shell_data->envp_array)
		return (perror("error allocating envp array"), false);
	if (!ft_copy_env_from_list_to_array(shell_data))
		return (false);
	return (true);
}

int	ft_get_number_of_env_variables(t_env *env_list)
{
	int	number_of_env_variables;

	number_of_env_variables = 0;
	while (env_list)
	{
		number_of_env_variables++;
		env_list = env_list->next;
	}
	return (number_of_env_variables);
}

bool	ft_copy_env_from_list_to_array(t_shell_data *shell_data)
{
	t_env	*env_list;
	int		i;

	env_list = shell_data->env_list;
	i = 0;
	while (env_list)
	{
		shell_data->envp_array[i] = ft_create_one_variable(env_list);
		if (!shell_data->envp_array[i])
			return (false);
		i++;
		env_list = env_list->next;
	}
	return (true);
}

char	*ft_create_one_variable(t_env *one_variable)
{
	char	*env_variable;
	char	*name_and_equal_sign;

	name_and_equal_sign = NULL;
	env_variable = NULL;
	name_and_equal_sign = ft_strjoin(one_variable->name, "=");
	if (!name_and_equal_sign)
		return (perror("error creating env name_and_equal_sign"), NULL);
	if (one_variable->value)
	{
		env_variable = ft_strjoin(name_and_equal_sign, one_variable->value);
		free(name_and_equal_sign);
		if (!env_variable)
			return (perror("error creating env_variable"), NULL);
		return (env_variable);
	}
	return (name_and_equal_sign);
}