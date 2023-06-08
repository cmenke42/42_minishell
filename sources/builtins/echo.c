/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:57:18 by npavelic          #+#    #+#             */
/*   Updated: 2023/06/08 12:32:05 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_min_n(char *str)
{
	if (ft_strlen(str) != 2)
		return (0);
	if ((str[0] != '-') || (str[1] != 'n'))
		return (0);
	return (1);
}

void	ft_echo(char **command)
{
	int		i;
	bool	print_new_line;

	i = 1;
	print_new_line = true;
	if (is_min_n(command[i]))
	{
		print_new_line = false;
		i++;
	}
	while (command[i])
		printf("%s", command[i++]);
	if (print_new_line == true)
		printf("%c", '\n');
	return ;
}
