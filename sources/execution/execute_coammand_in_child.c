/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_coammand_in_child.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:34:29 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/23 16:19:19 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 1 | 2 | 3 | 4 | 5 | 6

void	ft_execute_command_in_child(t_shell_data *shell_data, int number_of_commands, t_command_sequences *sequence_to_execute, int command_index)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (!ft_handle_redirection_operators(sequence_to_execute, sequence_to_execute->tokens))
		;
	else if (!ft_token_list_to_args_array(sequence_to_execute))
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
	return (false);
}

bool	ft_execute_builtin_if_builtin(t_shell_data *shell_data, t_command_sequences *sequence_to_execute)
{
	int		cmd_length;
	char	*command;

	command = sequence_to_execute->args[0];
	cmd_length = ft_strlen(command);
	//how to manage the calling of the builtin and the correct closing of the pipes, redirection and freeing?
	if (cmd_length < 2 || cmd_length > 6)
		return (false);
	if (!ft_strncmp("echo", command, cmd_length))
		ft_putstr_fd("builtin echo\n", 2);
	else if (!ft_strncmp("cd", command, cmd_length))
		ft_putstr_fd("builtin cd\n", 2);
	else if (!ft_strncmp("pwd", command, cmd_length))
		ft_putstr_fd("builtin pwd\n", 2);
	else if (!ft_strncmp("export", command, cmd_length))
		ft_putstr_fd("builtin export\n", 2);
	else if (!ft_strncmp("unset", command, cmd_length))
		ft_putstr_fd("builtin unset\n", 2);
	else if (!ft_strncmp("env", command, cmd_length))
		ft_putstr_fd("builtin env\n", 2);
	else if (!ft_strncmp("exit", command, cmd_length))
		ft_putstr_fd("builtin exit\n", 2);
	else
		return (false);
	exit(42); //remove later
}


bool	ft_check_if_cmd_path_is_valid(t_shell_data *shell_data, t_command_sequences *sequence_to_execute)
{
	if (access(sequence_to_execute->args[0], X_OK) == 0)
	{
		sequence_to_execute->command_path = sequence_to_execute->args[0];
		return (true);
	}
	if (!ft_env_list_to_envp_array(shell_data))
		return (false);
	sequence_to_execute->envp_command_paths = ft_get_envp_paths(shell_data->envp_array);
	sequence_to_execute->command_path = ft_get_cmd_path(sequence_to_execute->envp_command_paths, sequence_to_execute->args[0]);
	if (sequence_to_execute->command_path)
		return (true);
	ft_print_error_command_not_found(sequence_to_execute->args[0]);
	return (false);
}

void	ft_print_error_command_not_found(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
}