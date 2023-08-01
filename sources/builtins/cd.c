/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:49:18 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/01 21:16:18 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(char **command, t_list **env_list, t_shell_data *shell_data)
{
	char	*target_path;
	t_list	*env_variable_home;

	if (!command[1])
	{
		env_variable_home = ft_search_for_env_variable("HOME", *env_list);
		if (!env_variable_home)
			return (ft_put_err("cd: ", "HOME not set", __error));
		else
			target_path = ((t_env *)env_variable_home->content)->value;
	}
	else
		target_path = command[1];
	return (change_dir(env_list, target_path, shell_data));
}

int	ft_put_err(char *input, char *message, int code)
{
	ft_putstr_fd("minishell: ", 2);
	if (input)
		ft_putstr_fd(input, 2);
	ft_putendl_fd(message, 2);
	return (code);
}

int	assign_oldpwd(t_list *oldpwd, char *cwd_buf)
{
	cwd_buf = ft_calloc(MAXPATHLEN + 1, sizeof(char));
	if (!cwd_buf)
		return (perror("error creating cwd_buf for OLDPWD"),
			__system_call_error);
	if (!getcwd(cwd_buf, MAXPATHLEN))
		return (free(cwd_buf), perror("error getting cwd for pwd"),
			__system_call_error);
	ft_assign((t_env *)oldpwd->content, NULL, cwd_buf, "");
	return (__success);
}

int	change_dir(t_list **env_list, char *target_path, t_shell_data *shell_data)
{
	t_list	*pwd;
	t_list	*oldpwd;
	char	*cwd_buf;

	cwd_buf = NULL;
	oldpwd = ft_search_for_env_variable("OLDPWD", *env_list);
	pwd = ft_search_for_env_variable("PWD", *env_list);
	if (pwd && oldpwd)
	{
		ft_assign((t_env *)oldpwd->content, NULL,
			((t_env *)pwd->content)->value, "");
		((t_env *)pwd->content)->value = NULL;
	}
	else if (oldpwd && !pwd && shell_data->print_quotes_for_oldpwd)
	{
		ft_assign((t_env *)oldpwd->content, NULL, NULL, "");
		shell_data->print_quotes_for_oldpwd = false;
	}
	else if (oldpwd)
	{
		if (assign_oldpwd(oldpwd, cwd_buf))
			return (assign_oldpwd(oldpwd, cwd_buf));
	}
	return (cd_error_handler(target_path, pwd));
}

int	cd_error_handler(char *target_path, t_list *pwd)
{
	char	*cwd_buf;

	if (chdir(target_path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		perror(target_path);
		return (__error);
	}
	if (pwd)
	{
		cwd_buf = ft_calloc(MAXPATHLEN + 1, sizeof(char));
		if (!cwd_buf)
			return (perror("error creating cwd_bud"), __system_call_error);
		if (!getcwd(cwd_buf, MAXPATHLEN))
			return (free(cwd_buf), perror("error getting cwd for pwd"),
				__system_call_error);
		ft_assign((t_env *)pwd->content, NULL, cwd_buf, "");
	}
	return (__success);
}
