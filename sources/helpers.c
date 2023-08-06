/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:46:20 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/06 15:59:18 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_pipe_fds(int **pipe_fds, int number_of_pipes)
{
	int	i;

	i = 0;
	while (i < number_of_pipes)
	{
		printf("pipe_fds[%d][0] = %d\n", i, pipe_fds[i][0]);
		printf("pipe_fds[%d][1] = %d\n", i, pipe_fds[i][1]);
		i++;
	}
}

void	ft_print_envp_array(char **envp_array)
{
	int	i;

	i = 0;
	while (envp_array[i])
	{
		ft_putstr_fd("envp_array: ", 2);
		ft_putstr_fd(envp_array[i], 2);
		ft_putendl_fd("", 2);
		i++;
	}
}

void	ft_print_double_pointer(char **string)
{
	int	i;

	i = 0;
	while (string && string[i])
		printf("%s\n", string[i++]);
}

void	ft_print_command_sequences_args(t_list *cmd_sequences)
{
	t_cmd_sequences	*one_sequence;
	int				i;

	i = 0;
	while (cmd_sequences)
	{
		printf("\nSequence %d\n", i++);
		one_sequence = (t_cmd_sequences *)cmd_sequences->content;
		ft_print_double_array(one_sequence->args);
		cmd_sequences = cmd_sequences->next;
	}
}

void	ft_print_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("array[%d]: %s\n", i, array[i]);
		i++;
	}
}
