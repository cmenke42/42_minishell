/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke_close_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:25:35 by wmoughar          #+#    #+#             */
/*   Updated: 2023/08/05 02:30:58 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_builtin_command(t_shell_data *shell_data,
	t_cmd_sequences *sequence_to_execute, char *command, int status)
{
	if (!ft_strcmp("echo", command))
		ft_echo(sequence_to_execute->args);
	else if (!ft_strcmp("cd", command))
		status = ft_cd(sequence_to_execute->args, shell_data->env_list,
				&shell_data->print_quotes_for_oldpwd);
	else if (!ft_strcmp("pwd", command))
		status = ft_pwd(NULL, true);
	else if (!ft_strcmp("export", command))
		status = ft_export(sequence_to_execute->args, &shell_data->env_list);
	else if (!ft_strcmp("unset", command))
		status = ft_unset(sequence_to_execute->args, &shell_data->env_list,
				shell_data);
	else if (!ft_strcmp("env", command))
		ft_print_env_list(shell_data->env_list);
	else if (!ft_strcmp("exit", command))
		ft_exit(sequence_to_execute->args, shell_data);
	else
		return (__no_builtin_found);
	return (status);
}

void	ft_print_error(char *command, char *error_message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(error_message, 2);
}
