/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:20:03 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/26 23:18:52 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(char **command, t_list **env_list)
{
	char	*dir;
	t_list	*env_variable_home;
	t_list	*env_variable_oldpwd;

	if (!command[1])
	{
		env_variable_home = ft_search_for_env_variable("HOME", *env_list);
		if (!env_variable_home)
			return(ft_put_err("cd: ","HOME not set", 1));
		else
			dir = ((t_env *)env_variable_home->content)->value;
	}
	else if(command[2])
		return(ft_put_err("cd: ","Too many arguments", 2));
	else if (!ft_strcmp(command[1], "-"))
	{
		env_variable_oldpwd = ft_search_for_env_variable("OLDPWD", *env_list);
		if (!env_variable_oldpwd)
			return(ft_put_err("cd: ","OLDPWD not set", 1));
		else
		{
			dir = ((t_env *)env_variable_oldpwd->content)->value;
			printf("%s\n", dir);//why?
		}
	}
	else
		dir = command[1];
	return (change_dir(env_list, dir, env_variable_oldpwd));
}

int	ft_put_err(char *input, char *message, int code)
{
	ft_putstr_fd("minishell: ", 2);
	if (input)
		ft_putstr_fd(input, 2);
	ft_putendl_fd(message, 2);
	return (code);
}

int	change_dir(t_list **env_list, char *dir, t_list *env_variable_oldpwd)
{
	t_list	*env_variable_pwd;

	env_variable_pwd = ft_search_for_env_variable("PWD", *env_list);
	if (!env_variable_pwd)
		if (ft_store_one_variable_in_node(env_list, "PWD", true))
			return (__system_call_error); //handle error in shell
	if (!env_variable_oldpwd)
		if (ft_store_one_variable_in_node(env_list, "OLDPWD", true))
			return (__system_call_error); //handle error in shell
	if (cd_error_handler(dir))
		return (1);
	ft_assign_name_and_value_to_env_variable(env_variable_oldpwd, NULL, ((t_env *)env_variable_pwd->content)->value, ""); //cant do if value is needed in dir
	return (replace_pwd(env_list, env_variable_pwd, dir));
}

int	cd_error_handler(char *dir)
{
	char	*buffer = NULL;

	if (chdir(dir) == -1)
	{
		ft_putstr_fd("minishell: ", 1);
		perror(dir);
	} //handle error in shell
	buffer = getcwd(buffer, 100);
	free(buffer);
	return (0);
}

int	replace_pwd(t_list **env_list, t_list *env_variable_pwd, char *dir)
{
	char	*new_pwd;
	char	*buff;
	char	*pwd_and_slash;
	char	*result;

	buff = NULL;
	new_pwd = getcwd(buff, 100); //handle error in shell
	if (new_pwd)//only like this if it got allocated
		ft_assign_name_and_value_to_env_variable(env_variable_pwd, NULL, new_pwd, "");
	else
	{
		pwd_and_slash = ft_strjoin("/", dir);
		update_value(env, "PWD", ft_strjoin(temp->value,
				ft_strjoin("/", dir)));
		printf("%s\n", temp->value);//why?
	}
	return (0);
}