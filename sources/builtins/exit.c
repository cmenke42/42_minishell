/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:15:06 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/31 18:58:29 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char **args, t_shell_data *shell_data)
{
	int		exit_code;
	bool	print_exit;

	exit_code = 0;
	print_exit = true;
	if (!args[1])
		;
	else if (args[2])
	{
		print_exit = false;
		printf("exit\n");
		ft_print_error("exit:", " too many arguments");
		exit_code = 1;
	}
	else
		exit_code = ft_exit_code(args[1], &print_exit);
	ft_free_shell_data(shell_data, true);
	if (print_exit)
		printf("exit\n");
	exit(exit_code);
}

int	ft_exit_code(char *str, bool *print_exit)
{
	int	exit_code;

	if (ft_is_str_digit(str))
		exit_code = ft_atoi(str);
	else
	{
		*print_exit = false;
		printf("exit\n");
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(" : numeric argument required\n", STDERR_FILENO);
		exit_code = 255;
	}
	return (exit_code);
}

int	ft_is_str_digit(char *str)
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
