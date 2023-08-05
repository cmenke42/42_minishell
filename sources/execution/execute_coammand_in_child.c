/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_coammand_in_child.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:34:29 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/05 02:36:24 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execute_command_in_child(t_shell_data *shell_data,
	int number_of_commands, t_cmd_sequences *sequence_to_execute,
	int command_index)
{
	int	exit_code;

	ft_restore_default_signals();
	shell_data->exit_code = 1;
	if (ft_handle_redirection_operators(sequence_to_execute,
			sequence_to_execute->tokens, shell_data->heredocs))
		;
	else if (!ft_token_list_to_args_array(&sequence_to_execute->args,
			sequence_to_execute->tokens))
		;
	else if (!ft_env_list_to_envp_array(shell_data))
		;
	else if (!ft_duplication_of_fds(shell_data->pipe_fds, sequence_to_execute,
			number_of_commands, command_index))
		;
	else if (ft_execution_of_command(shell_data, sequence_to_execute, false))
		;
	exit_code = shell_data->exit_code;
	rl_clear_history();
	ft_close_all_pipes(shell_data->pipe_fds, number_of_commands - 1);
	ft_free_double_pointer_int(&shell_data->pipe_fds, number_of_commands - 1);
	ft_free_shell_data(shell_data, true);
	exit(exit_code);
}

int	ft_execution_of_command(t_shell_data *shell_data,
	t_cmd_sequences *sequence_to_execute, bool single_builtin)
{
	int	status;

	status = ft_execute_builtin_if_builtin(shell_data, sequence_to_execute);
	if (single_builtin)
		return (status);
	else if (!single_builtin && status != __no_builtin_found)
		return (status);
	else if (!ft_check_if_cmd_path_is_valid(shell_data, sequence_to_execute))
		;
	else if (execve(sequence_to_execute->command_path,
			sequence_to_execute->args, shell_data->envp_array) == -1)
		perror("minishell: execve");
	return (__mini_error);
}

int	ft_execute_builtin_if_builtin(t_shell_data *shell_data,
	t_cmd_sequences *sequence_to_execute)
{
	char	*command;
	int		status;

	status = __success;
	command = sequence_to_execute->args[0];
	status = get_builtin_command(shell_data, sequence_to_execute, command,
			status);
	if (status == __success)
		shell_data->exit_code = 0;
	return (status);
}

bool	ft_check_if_cmd_path_is_valid(t_shell_data *shell_data,
	t_cmd_sequences *sequence_to_execute)
{
	struct stat	file_info;

	if (sequence_to_execute->args[0][0] == '\0')
	{
		shell_data->exit_code = 127;
		ft_print_error(sequence_to_execute->args[0], ": command not found\n");
		return (false);
	}
	assign_sequence_to_path(shell_data, sequence_to_execute);
	if (sequence_to_execute->command_path)
		return (true);
	if (access(sequence_to_execute->args[0], F_OK) == 0)
	{
		if (!is_file_directory(shell_data, sequence_to_execute, file_info))
			return (false);
		else if (is_file_executable(shell_data, sequence_to_execute, file_info))
			return (true);
		else if (!handle_non_exe(shell_data, sequence_to_execute, file_info))
			return (false);
	}
	else if (!is_path_invalid(shell_data, sequence_to_execute))
		return (false);
	ft_print_error(sequence_to_execute->args[0], ": command not found\n");
	shell_data->exit_code = 127;
	return (false);
}

bool	ft_is_slash_in_command(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
			return (true);
		i++;
	}
	return (false);
}
