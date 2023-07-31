/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:49:18 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/31 12:04:27 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(char **command, t_list **env_list)
{
	char	*target_path;
	t_list	*env_variable_home;
	t_list	*env_variable_oldpwd;

	env_variable_oldpwd = ft_search_for_env_variable("OLDPWD", *env_list);
	if (!command[1])
	{
		env_variable_home = ft_search_for_env_variable("HOME", *env_list);
		if (!env_variable_home)
			return(ft_put_err("cd: ","HOME not set", 1), __error);
		else
			target_path = ((t_env *)env_variable_home->content)->value;
	}
	else
		target_path = command[1];
	if (change_dir(env_list, target_path, env_variable_oldpwd) == __system_call_error)
		return (__system_call_error);
	return (__success);
}

int	ft_put_err(char *input, char *message, int code)
{
	ft_putstr_fd("minishell: ", 2);
	if (input)
		ft_putstr_fd(input, 2);
	ft_putendl_fd(message, 2);
	return (code);
}

int	change_dir(t_list **env_list, char *target_path, t_list *env_variable_oldpwd)
{
	t_list	*env_variable_pwd;
	
	env_variable_pwd = ft_search_for_env_variable("PWD", *env_list);
	if (env_variable_pwd && env_variable_oldpwd)
		ft_assign_name_and_value_to_env_variable((t_env *)env_variable_oldpwd->content, NULL, ((t_env *)env_variable_pwd->content)->value, "");
	((t_env *)env_variable_pwd->content)->value = NULL;
	if (cd_error_handler(target_path, env_variable_pwd) == __system_call_error)
		return (__system_call_error);
	// return (replace_pwd(env_variable_pwd, target_path));
	return (__success);
}

int	cd_error_handler(char *target_path, t_list *env_variable_pwd)
{
	char	*cwd_buf;

	if (chdir(target_path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		perror(target_path);
		return (__error);
	} //handle error in shell
	cwd_buf = ft_calloc(MAXPATHLEN + 1, sizeof(char));
	if (!cwd_buf)
		return (perror("error creating cwd_bud"), __system_call_error);
	if (!getcwd(cwd_buf, MAXPATHLEN))
		return (free(cwd_buf), perror("error getting cwd for pwd"), __system_call_error);
	if (env_variable_pwd)
		ft_assign_name_and_value_to_env_variable((t_env *)env_variable_pwd->content, NULL, cwd_buf, "");
	return (__success);
}

// int	replace_pwd(t_list *env_variable_pwd, char *dir)
// {
// 	char	*new_pwd;
// 	char	*buff;
// 	char	*pwd_and_slash;
// 	char	*result;

// 	buff = NULL;
// 	new_pwd = getcwd(buff, PATH_MAX); //handle error in shell
// 	if (new_pwd)//only like this if it got allocated
// 		ft_assign_name_and_value_to_env_variable((t_env *)env_variable_pwd->content, NULL, new_pwd, "");
// 	else
// 	{
// 		if (dir)
// 			pwd_and_slash = ft_strjoin("/", dir);
// 		else
// 			pwd_and_slash = ft_strdup("/");
// 		if (!pwd_and_slash)
// 			return (ft_free_pointer_and_set_to_null((void **)&dir), __system_call_error); //handle error in shell
// 		if (((t_env *)env_variable_pwd->content)->value)
// 			result = ft_strjoin(((t_env *)env_variable_pwd->content)->value, pwd_and_slash);
// 		else
// 			result = ft_strdup(pwd_and_slash);
// 		ft_free_pointer_and_set_to_null((void **)&dir);
// 		if (!result)
// 			return (ft_free_pointer_and_set_to_null((void **)&pwd_and_slash), __system_call_error); //handle error in shell
// 		printf("%s\n", ((t_env *)env_variable_pwd->content)->value);//why?
// 	}
// 	return (0);
// }