/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_builtin_execution.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:50:13 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/30 17:10:39 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_execute_single_builtin(t_shell_data *shell_data, int number_of_commands, t_command_sequences *sequence_to_execute, int command_index)
{
	shell_data->exit_code = 1;
	if (!ft_save_standard_fds(shell_data))
		return (false);
	ft_restore_default_signals();
	if (!ft_handle_redirection_operators(sequence_to_execute, sequence_to_execute->tokens, shell_data))
		;
	else if (!ft_token_list_to_args_array(sequence_to_execute))
		;
	else if (!ft_duplication_of_fds(shell_data->pipe_fds, sequence_to_execute, number_of_commands, command_index))
		;
	else if (ft_execution_of_command(shell_data, sequence_to_execute, true))
		;
	else if (!ft_restore_standard_fds(shell_data))
		;
	else
		return (true);
	return (false);
}

bool	ft_is_builtin(t_command_sequences *sequence_to_execute)
{
	char	*command;
	t_tokens	*token;

	token = (t_tokens *)sequence_to_execute->tokens->content;
	command = token->token;
	if (!ft_strcmp("echo", command))
		return (true);
	else if (!ft_strcmp("cd", command))
		return (true);
	else if (!ft_strcmp("pwd", command))
		return (true);
	else if (!ft_strcmp("export", command))
		return (true);
	else if (!ft_strcmp("unset", command))
		return (true);
	else if (!ft_strcmp("env", command))
		return (true);
	else if (!ft_strcmp("exit", command))
		return (true);
	else
		return (false);
}

bool	ft_save_standard_fds(t_shell_data *shell_data)
{
	shell_data->default_stdin = dup(STDIN_FILENO);
	if (shell_data->default_stdin == -1)
		return (perror("error saving default stdin"), false);
	shell_data->default_stdout = dup(STDOUT_FILENO);
	if (shell_data->default_stdout == -1)
	{
		close(shell_data->default_stdin);
		return (perror("error saving default stdout"), false);
	}
	return (true);
}

bool	ft_restore_standard_fds(t_shell_data *shell_data)
{
	bool	status;

	status = true;
	if (dup2(shell_data->default_stdin, STDIN_FILENO) == -1)
	{
		perror("error restoring default stdin");
		status = false;
	}
	else if (dup2(shell_data->default_stdout, STDOUT_FILENO) == -1)
	{
		perror("error restoring default stdout");
		status = false;
	}
	return (status);
}
