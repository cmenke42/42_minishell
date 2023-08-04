/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:52:58 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/04 19:06:55 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_prepare_minishell(t_shell_data **shell_data, char **envp)
{
	*shell_data = ft_calloc(1, sizeof(t_shell_data));
	if (!*shell_data)
		return (perror("shell_data struct allocation error"), exit(1), 1);
	if (ft_store_env_in_list(envp, &(*shell_data)->env_list) == __system_call_error)
		return (printf("error storing env in list\n"), ft_free_shell_data(*shell_data, true), exit(1), 1);
	if (ft_prepare_env_variables(*shell_data) == __system_call_error)
		return (ft_free_shell_data(*shell_data, true), exit(1), 1);
	ft_set_minisell_signals();
	return (0);
}

int	ft_prepare_env_variables(t_shell_data *shell_data)
{
	char *pwd_name;
	char *pwd_value;

	pwd_value = NULL;
	if (increase_shlvl(&shell_data->env_list) == __system_call_error)
		return (__system_call_error);
	if (ft_update_or_add_env_variable("OLDPWD", &shell_data->env_list, NULL, NULL) == __system_call_error)
		return (__system_call_error);
	if (!ft_search_for_env_variable("PWD", shell_data->env_list))
	{
		pwd_name = ft_strdup("PWD");
		if (!pwd_name)
			return (perror("error creating name in ft_prepare_env_variables"), __system_call_error);
		ft_pwd(&pwd_value, false);
		if (ft_update_or_add_env_variable(NULL, &shell_data->env_list, pwd_name, pwd_value) == __system_call_error)
			return (__system_call_error);
	}
	return (__success);
}

int	increase_shlvl(t_list **env_list)
{
	t_list	*shlvl;
	char	*name;
	char	*value;

	name = ft_strdup("SHLVL");
	if (!name)
		return (perror("error creating name in increase_shlvl"), __system_call_error);
	shlvl = ft_search_for_env_variable("SHLVL", *env_list);
	if (!shlvl || !((t_env*)shlvl->content)->value)
	{
		value = ft_strdup("1");
		if (!value)
			return (free(name), perror("error creating strudp value in increase_shlvl"), __system_call_error);
		if (store_var_in_node(env_list, name, value, "=") == __system_call_error)
			return (free(name), free(value), __system_call_error);
		return (__success);
	}
	value = ft_itoa(ft_atoi(((t_env*)shlvl->content)->value) + 1);
	if (!value)
		return (free(name), perror("error creating itoa value in increase_shlvl"), __system_call_error);
	ft_assign((t_env *)shlvl->content, name, value, "=");
	return (__success);
}
