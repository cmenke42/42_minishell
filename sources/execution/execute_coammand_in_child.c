/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_coammand_in_child.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:34:29 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/31 11:07:45 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 1 | 2 | 3 | 4 | 5 | 6

void	ft_execute_command_in_child(t_shell_data *shell_data, int number_of_commands, t_command_sequences *sequence_to_execute, int command_index)
{
	int	exit_code;
	ft_restore_default_signals();
	shell_data->exit_code = 1;
	if (!ft_handle_redirection_operators(sequence_to_execute, sequence_to_execute->tokens, shell_data))
		;
	else if (!ft_token_list_to_args_array(sequence_to_execute))
		;
	else if (!ft_env_list_to_envp_array(shell_data))
		;
	else if (!ft_duplication_of_fds(shell_data->pipe_fds, sequence_to_execute, number_of_commands, command_index))
		;
	else if (ft_execution_of_command(shell_data, sequence_to_execute, false))
		;
	exit_code = shell_data->exit_code;
	ft_free_shell_data(shell_data, true);
	exit(exit_code);
}

int	ft_execution_of_command(t_shell_data *shell_data, t_command_sequences *sequence_to_execute, bool single_builtin)
{
	int	status;

	status = ft_execute_builtin_if_builtin(shell_data, sequence_to_execute);
	if (single_builtin)
		return (status);
	else if (!single_builtin && status != __no_builtin_found)
		return (status);
	else if (!ft_check_if_cmd_path_is_valid(shell_data, sequence_to_execute))
		;
	else if (execve(sequence_to_execute->command_path, sequence_to_execute->args, shell_data->envp_array) == -1)
		perror("minishell: execve");
	return (__error);
}

int	ft_execute_builtin_if_builtin(t_shell_data *shell_data, t_command_sequences *sequence_to_execute)
{
	char	*command;
	int		status;

	status = __success;
	command = sequence_to_execute->args[0];
	if (!ft_strcmp("echo", command))
		ft_echo(sequence_to_execute->args);
	else if (!ft_strcmp("cd", command))
		status = ft_cd(sequence_to_execute->args, &shell_data->env_list); //error
	else if (!ft_strcmp("pwd", command))
		status = ft_pwd(NULL, true); //error
	else if (!ft_strcmp("export", command))
		status = ft_export(sequence_to_execute->args, &shell_data->env_list); //system call error possible
	else if (!ft_strcmp("unset", command))
		status = ft_unset(sequence_to_execute->args, &shell_data->env_list); //syntax error possible
	else if (!ft_strcmp("env", command))
		ft_print_env_list(shell_data->env_list);
	else if (!ft_strcmp("exit", command))
		ft_exit(sequence_to_execute->args, shell_data);
	else
		return (__no_builtin_found);
	if (status == __success)
		shell_data->exit_code = 0;
	return (status);
}


bool	ft_check_if_cmd_path_is_valid(t_shell_data *shell_data, t_command_sequences *sequence_to_execute)
{
	if (sequence_to_execute->args[0][0] == '\0') //for emtpy quotes as input
	{
		shell_data->exit_code = 127;
		ft_print_error_command_not_found(sequence_to_execute->args[0]);
		return (false);
	}
	sequence_to_execute->envp_command_paths = ft_get_envp_paths(shell_data->envp_array);
	sequence_to_execute->command_path = ft_get_cmd_path(sequence_to_execute->envp_command_paths, sequence_to_execute->args[0]);
	if (sequence_to_execute->command_path)
		return (true);
	if (access(sequence_to_execute->args[0], F_OK) == 0) //if file exists
	{
		if (access(sequence_to_execute->args[0], X_OK) == 0)
		{
			sequence_to_execute->command_path = ft_strdup(sequence_to_execute->args[0]);
			if (!sequence_to_execute->command_path)
				return (perror("error in ft_strdup sequence_to_execute->args[0]"), false);
			return (true);
		}
		else
		{
			shell_data->exit_code = 126;
			ft_putstr_fd("minishell: ", 2);
			perror(sequence_to_execute->args[0]);
			return (false);
		}
	}
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