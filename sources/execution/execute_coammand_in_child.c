/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_coammand_in_child.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:34:29 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/25 17:23:57 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 1 | 2 | 3 | 4 | 5 | 6

void	ft_execute_command_in_child(t_shell_data *shell_data, int number_of_commands, t_command_sequences *sequence_to_execute, int command_index)
{
	ft_restore_default_signals();
	if (!ft_handle_redirection_operators(sequence_to_execute, sequence_to_execute->tokens))
		;
	else if (!ft_token_list_to_args_array(sequence_to_execute))
		;
	else if (!ft_env_list_to_envp_array(shell_data))
		;
	else if (!ft_duplication_of_fds(shell_data->pipe_fds, sequence_to_execute, number_of_commands, command_index))
		;
	else if (!ft_execution_of_command(shell_data, sequence_to_execute, false))
		;
	//clear up
	ft_free_shell_data_for_next_command(shell_data); // for testing, needs to free everything
	exit(1);
}


bool	ft_execution_of_command(t_shell_data *shell_data, t_command_sequences *sequence_to_execute, bool single_builtin)
{
	if (ft_execute_builtin_if_builtin(shell_data, sequence_to_execute, single_builtin) && single_builtin) //exit after executing builtin
		return (true);
	else if (!ft_check_if_cmd_path_is_valid(shell_data, sequence_to_execute))
		;
	else if (execve(sequence_to_execute->command_path, sequence_to_execute->args, shell_data->envp_array) == -1)
		perror("error executing command");
	return (false);
}

bool	ft_execute_builtin_if_builtin(t_shell_data *shell_data, t_command_sequences *sequence_to_execute, bool single_builtin)
{
	int		cmd_length;
	char	*command;

	command = sequence_to_execute->args[0];
	if (!command)
		return (false);
	cmd_length = ft_strlen(command);
	if (cmd_length == 0)
		return (false);
	if (cmd_length == 4 && !ft_strncmp("echo", command, cmd_length))
		ft_echo(sequence_to_execute->args);
	else if (cmd_length == 2 && !ft_strncmp("cd", command, cmd_length))
		ft_cd(sequence_to_execute->args, shell_data->env_list);
	else if (cmd_length == 3 && !ft_strncmp("pwd", command, cmd_length))
		ft_pwd();
	else if (cmd_length == 6 && !ft_strncmp("export", command, cmd_length))
		ft_export(sequence_to_execute->args, shell_data->env_list);
	else if (cmd_length == 5 && !ft_strncmp("unset", command, cmd_length))
		ft_unset(sequence_to_execute->args, shell_data->env_list);
	else if (cmd_length == 3 && !ft_strncmp("env", command, cmd_length))
		print_env(shell_data->env_list);
	else if (cmd_length == 4 && !ft_strncmp("exit", command, cmd_length))
		ft_exit(sequence_to_execute->args);
	else
		return (false);
	if (single_builtin == false)
		exit(0); //remove later
	return (true);
}


bool	ft_check_if_cmd_path_is_valid(t_shell_data *shell_data, t_command_sequences *sequence_to_execute)
{
	if (sequence_to_execute->args[0][0] == '\0')
	{
		ft_print_error_command_not_found(sequence_to_execute->args[0]);
		return (false);
	}
	if (access(sequence_to_execute->args[0], X_OK) == 0)
	{
		sequence_to_execute->command_path = sequence_to_execute->args[0];
		return (true);
	}
	sequence_to_execute->envp_command_paths = ft_get_envp_paths(shell_data->envp_array);
	sequence_to_execute->command_path = ft_get_cmd_path(sequence_to_execute->envp_command_paths, sequence_to_execute->args[0]);
	if (sequence_to_execute->command_path)
		return (true);
	ft_print_error_command_not_found(sequence_to_execute->args[0]);
	shell_data->exit_code = 127;
	return (false);
}

void	ft_print_error_command_not_found(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
}