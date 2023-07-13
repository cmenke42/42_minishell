/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:20:03 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/13 15:34:43 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"
#include <stdio.h>

int	*replace_pwd(t_env *env, t_env *temp, char *dir)
{
	char	*new_pwd;
	char	*buff;

	buff = NULL;
	new_pwd = getcwd(buff, 100);
	if (new_pwd)
		update_value(env, "PWD", new_pwd);
	else
	{
		update_value(env, "PWD", ft_strjoin(temp->value,
				ft_strjoin("/", dir)));
		printf("%s\n", temp->value);
	}
	free(new_pwd);
	return (0);
}

int	change_dir(t_env *env, char *dir)
{
	t_env	*tmp;
	
	tmp = ft_search(env, "PWD");
	if (!tmp)
		add_to_list(env, reverse_split("PWD", ""));
	tmp = ft_search(env, "OLDPWD");
	if (!tmp)
		add_to_list(env, "OLDPWD");
	if (cd_error_handler(dir))
		return (1);
	tmp = ft_search(env, "PWD");
	update_value(env, "OLDPWD", tmp->value);
	return (replace_pwd(env, tmp, dir));
}

int	ft_cd(char **command, t_env	*env)
{
	char	*dir;
	t_env	*tmp;

	if (!command[1])
	{
		tmp = ft_search(env, "HOME");
		if (!tmp)
			return(ft_put_err("cd: ","HOME not set", 1));
		else
			dir = tmp->value;
	}
	else if(command[2])
		return(ft_put_err("cd: ","Too many arguments", 2));
	else if (!(ft_strncmp(command[1], "-", ft_strlen(command[1]))))
	{
		tmp = ft_search(env, "OLDPWD");
		if (!tmp)
			return(ft_put_err("cd: ","OLDPWD not set", 1));
		else
		{
			dir = tmp->value;
			printf("%s\n", dir);
		}
	}
	else
		dir = command[1];
	return (change_dir(env, dir));
}