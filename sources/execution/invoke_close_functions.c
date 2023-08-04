/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke_close_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:25:35 by wmoughar          #+#    #+#             */
/*   Updated: 2023/08/04 19:23:01 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	call_functions(t_shell_data *shell_data, int number_of_commands)
{
	ft_close_all_pipes(shell_data->pipe_fds, number_of_commands - 1);
	ft_free_double_pointer_int(&shell_data->pipe_fds, number_of_commands - 1);
	ft_wait_for_childs_and_get_exit_code(shell_data, number_of_commands);
	ft_set_minisell_signals();
}

int	get_builtin_command(t_shell_data *shell_data,
	t_cmd_sequences *sequence_to_execute, char *command, int status)
{
	if (!ft_strcmp("echo", command))
		ft_echo(sequence_to_execute->args);
	else if (!ft_strcmp("cd", command))
		status = ft_cd(sequence_to_execute->args, &shell_data->env_list,
				shell_data); //error
	else if (!ft_strcmp("pwd", command))
		status = ft_pwd(NULL, true); //error
	else if (!ft_strcmp("export", command))
		status = ft_export(sequence_to_execute->args, &shell_data->env_list); //system call error possible
	else if (!ft_strcmp("unset", command))
		status = ft_unset(sequence_to_execute->args, &shell_data->env_list,
				shell_data); //syntax error possible
	else if (!ft_strcmp("env", command))
		ft_print_env_list(shell_data->env_list);
	else if (!ft_strcmp("exit", command))
		ft_exit(sequence_to_execute->args, shell_data);
	else
		return (__no_builtin_found);
	return (status);
}
