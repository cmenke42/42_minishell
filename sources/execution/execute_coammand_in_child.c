/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_coammand_in_child.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:34:29 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/22 18:35:11 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 1 | 2 | 3 | 4 | 5 | 6

void	ft_execute_command_in_child(t_shell_data *shell_data, int number_of_commands, t_command_sequences *sequence_to_execute, int command_index)
{
	if (!ft_handle_redirection_operators(sequence_to_execute, sequence_to_execute->tokens))
		;
	else if (!ft_token_list_to_char_array(sequence_to_execute))
		;
	else if (!ft_duplication_of_fds(shell_data->pipe_fds, sequence_to_execute, number_of_commands, command_index))
		;

	ft_putstr_fd("child process:", 1);
	ft_putnbr_fd(command_index, 1);
	ft_putstr_fd("\n", 1);
	exit(22);
}
