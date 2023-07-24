/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_builtin_execution.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:50:13 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/24 15:52:55 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_builtin(t_shell_data *shell_data, t_command_sequences *sequence_to_execute)
{
	int		cmd_length;
	char	*command;
	t_tokens	*token;

	token = (t_tokens *)sequence_to_execute->tokens->content;
	command = token->token;
	if (!command)
		return (false);
	cmd_length = ft_strlen(command);
	if (cmd_length == 0)
		return (false);
	if (cmd_length == 4 && !ft_strncmp("echo", command, cmd_length))
		return (true);
	else if (cmd_length == 2 && !ft_strncmp("cd", command, cmd_length))
		return (true);
	else if (cmd_length == 3 && !ft_strncmp("pwd", command, cmd_length))
		return (true);
	else if (cmd_length == 6 && !ft_strncmp("export", command, cmd_length))
		return (true);
	else if (cmd_length == 5 && !ft_strncmp("unset", command, cmd_length))
		return (true);
	else if (cmd_length == 3 && !ft_strncmp("env", command, cmd_length))
		return (true);
	else if (cmd_length == 4 && !ft_strncmp("exit", command, cmd_length))
		return (true);
	else
		return (false);
}