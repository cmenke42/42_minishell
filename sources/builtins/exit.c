/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:15:06 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/25 18:52:36 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_code(char *str)
{
	int	exit_code;

	printf("exit\n");
	if (is_str_digit(str))
		exit_code = ft_atoi(str);
	else
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(" :numeric argument required\n", STDERR_FILENO);
		exit_code = 255;
	}
	free(str);
	exit(exit_code);
}

void	ft_exit(char **args)
{
	if (!args[1])
	{
		printf("exit\n");
		exit(0);
	}
	if (args[2])
	{
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
		exit(1);
	}
	exit_code(args[1]);
}