/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:15:06 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/10 21:24:41 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"

void	ft_exit(void)
{
	printf("exit\n");
	exit(0);
}

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

	if (is_str_digit(str))
		exit_code = ft_atoi(str);
	else
	{
		printf("bash: exit: %s: numeric argument required\n", str);
		exit_code = 255;
	}
	printf("exit\n");
	free(str);
	exit(exit_code);
}
