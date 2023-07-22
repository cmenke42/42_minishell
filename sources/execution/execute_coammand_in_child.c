/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_coammand_in_child.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:34:29 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/22 20:11:19 by cmenke           ###   ########.fr       */
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
	else if (!ft_execution_of_command(shell_data, sequence_to_execute))
		;
	//clear up
	exit(1);
}


bool	ft_execution_of_command(t_shell_data *shell_data, t_command_sequences *sequence_to_execute)
{
	if (ft_execute_builtin_if_builtin(shell_data, sequence_to_execute)) //exit after executing builtin
		;
	else if (!ft_check_if_cmd_path_is_valid(shell_data, sequence_to_execute))
		;
	else if (execve(sequence_to_execute->command_path, sequence_to_execute->args, shell_data->envp_array) == -1)
		perror("error executing command");
	else
		return (true);
	return (false);
}

bool	ft_execute_builtin_if_builtin(t_shell_data *shell_data, t_command_sequences *sequence_to_execute)
{
	return (false);
}


bool	ft_check_if_cmd_path_is_valid(t_shell_data *shell_data, t_command_sequences *one_sequence)
{
	if (access(one_sequence->args[0], X_OK) == 0)
	{
		one_sequence->command_path = one_sequence->args[0];
		return (true);
	}
	if (!ft_env_list_to_char_array(shell_data))
		return (false);
	one_sequence->envp_command_paths = ft_get_envp_paths(shell_data->envp_array);
	one_sequence->command_path = ft_get_cmd_path(one_sequence->envp_command_paths, one_sequence->args[0]);
	if (one_sequence->command_path)
		return (true);
	perror("command not found");
	return (false);
}