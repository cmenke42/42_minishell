/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:57:18 by npavelic          #+#    #+#             */
/*   Updated: 2023/07/11 19:18:53 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int	is_min_n(char *str)
// {
// 	if (ft_strlen(str) != 2)
// 		return (0);
// 	if ((str[0] != '-') || (str[1] != 'n'))
// 		return (0);
// 	return (1);
// }

// void	ft_echo(char **command)
// {
// 	int		i;
// 	bool	print_new_line;

// 	i = 1;
// 	print_new_line = true;
// 	if (is_min_n(command[i]))
// 	{
// 		print_new_line = false;
// 		i++;
// 	}
// 	while (command[i])
// 	{
// 		printf("%s", command[i++]);
// 		if (command[i])
// 			printf(" ");
// 	}
// 	if (print_new_line == false && !ft_strncmp(command[2], "-n", sizeof(command[2])
// 		&& !command[3]))
// 		return ;
// 	if (print_new_line == false && !ft_strncmp(command[2], "-n", sizeof(command[2])
// 		&& command[3]))
// 	if (print_new_line == true)
// 		printf("%c", '\n');
// 	return ;
// }

void	print_lines(int i, char **str)
{
	while (str[i])
	{
		printf("%s", str[i++]);
		if (str[i])
			printf(" ");
	}
}

int	ft_echo(char **command)
{
	int		i;
	int		j;
	bool	n_flag;

	i = 1;
	n_flag = false;
	while (command[i] && command[i][0] == '-'
		&& command[i][1] == 'n')
	{
		j = 1;
		while (command[i][j] == 'n')
			j++;
		if (command[i][j] == '\0')
			n_flag = true;
		else
			break ;
		i++;
	}
	print_lines(i, command);
	if (n_flag == false)
		printf("\n");
	return (EXIT_SUCCESS);
}