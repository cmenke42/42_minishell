/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:30:23 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/25 12:17:20 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

int	ft_pwd(void)
{
	char *path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		printf("minishell: path doesn't exist\n");
		return 0;
	}
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	free(path);
	return 0;
}
