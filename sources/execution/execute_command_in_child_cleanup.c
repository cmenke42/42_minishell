/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_in_child_cleanup.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:20:42 by wmoughar          #+#    #+#             */
/*   Updated: 2023/08/05 00:07:40 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	assign_sequence_to_path(t_shell_data *shell_data,
	t_cmd_sequences *sequence_to_execute)
{
	sequence_to_execute->envp_command_paths
		= ft_get_envp_paths(shell_data->envp_array);
	sequence_to_execute->command_path
		= ft_get_cmd_path(sequence_to_execute->envp_command_paths,
			sequence_to_execute->args[0]);
}	

bool	is_file_directory(t_shell_data *shell_data,
	t_cmd_sequences *sequence_to_execute, struct stat file_info)
{
	if (stat(sequence_to_execute->args[0], &file_info) == 0
		&& ft_is_slash_in_command(sequence_to_execute->args[0]))
	{
		if (S_ISDIR(file_info.st_mode))
		{
			shell_data->exit_code = 126;
			ft_print_error(sequence_to_execute->args[0], ": is a directory\n");
			return (false);
		}
	}
	return (true);
}

bool	is_file_executable(t_shell_data *shell_data,
	t_cmd_sequences *sequence_to_execute, struct stat file_info)
{
	if (access(sequence_to_execute->args[0], X_OK) == 0
		&& !S_ISDIR(file_info.st_mode))
	{
		shell_data->exit_code = 126;
		sequence_to_execute->command_path
			= ft_strdup(sequence_to_execute->args[0]);
		if (!sequence_to_execute->command_path)
			return (perror("error in ft_strdup sequence_to_execute->args[0]"),
				false);
		return (true);
	}
	return (true);
}

bool	handle_non_exe(t_shell_data *shell_data,
	t_cmd_sequences *sequence_to_execute, struct stat file_info)
{
	if (!S_ISDIR(file_info.st_mode)
		&& ft_is_slash_in_command(sequence_to_execute->args[0]))
	{
		shell_data->exit_code = 126;
		ft_putstr_fd("minishell: ", 2);
		perror(sequence_to_execute->args[0]);
		return (false);
	}
	return (true);
}

bool	is_path_invalid(t_shell_data *shell_data,
	t_cmd_sequences *sequence_to_execute)
{
	if (ft_is_slash_in_command(sequence_to_execute->args[0])
		|| !ft_search_for_env_variable("PATH", shell_data->env_list))
	{
		shell_data->exit_code = 127;
		ft_putstr_fd("minishell: ", 2);
		perror(sequence_to_execute->args[0]);
		return (false);
	}
	return (true);
}
