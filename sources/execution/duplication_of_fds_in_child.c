/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplication_of_fds_in_child.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:23:14 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/22 19:33:43 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_duplication_of_fds(int **pipe_fds, t_command_sequences *sequence_to_execute, int number_of_commands, int command_index)
{
	bool	status;

	status = true;
	if(!ft_input_redirection_in_child(pipe_fds, sequence_to_execute->input_fd, command_index))
		status = false;
	if(!ft_output_redirection_in_child(pipe_fds, sequence_to_execute->output_fd, number_of_commands, command_index))
		status = false;
	ft_close_all_pipes(pipe_fds, number_of_commands);
	return (status);
}

bool	ft_input_redirection_in_child(int **pipe_fds, int input_fd, int command_index)
{
	if (input_fd != 0)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			return (perror("error duplicating input fd"), false);
	}
	else if (command_index > 0)
	{
		if (dup2(pipe_fds[command_index - 1][0], STDIN_FILENO) == -1)
			return (perror("error duplicating pipe read end"), false);
	}
	return (true);
}

bool	ft_output_redirection_in_child(int **pipe_fds, int output_fd, int number_of_commands, int command_index)
{
	if (output_fd != 1)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
			return (perror("error duplicating output fd"), false);
	}
	if (command_index < number_of_commands - 1)
	{
		if (dup2(pipe_fds[command_index][1], STDOUT_FILENO) == -1)
			return (perror("error duplicating pipe write end"), false);
	}
	return (true);
}

// void	ft_close_pipes_except_for_needed_ones(int **pipe_fds, int number_of_pipes, int command_index)
// {
// 	int	i;

// 	i = 0;
// 	while (i < number_of_pipes - 1)
// 	{
// 		if (i != command_index - 1)
// 			close(pipe_fds[i][0]);
// 		if (i != command_index)
// 			close(pipe_fds[i][1]);
// 		i++;
// 	}
// }

void	ft_close_all_pipes(int **pipe_fds, int number_of_pipes)
{
	int	i;

	i = 0;
	while (i < number_of_pipes - 1)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		i++;
	}
}
