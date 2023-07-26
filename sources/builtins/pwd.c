/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:30:23 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/26 22:30:21 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char *path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_putstr_fd("minishell: path doesn't exist\n", 2);
		return (__system_call_error);//catch rigt exit code in shell
	}
	printf("%s\n", path);
	free(path);
	return (__success);
}
