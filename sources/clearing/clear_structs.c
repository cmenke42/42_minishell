/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:08:25 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/28 20:27:41 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//in main programm

void	ft_free_shell_data_for_next_command(t_shell_data *shell_data)
{
	ft_free_pointer_and_set_to_null((void **)&shell_data->command_line_read);
	ft_free_double_pointer_char(&shell_data->envp_array);
	ft_free_pointer_and_set_to_null((void **)&shell_data->process_ids);
	ft_free_double_pointer_char(&shell_data->heredocs);
	if (shell_data->command_sequences)
		ft_lstclear(&shell_data->command_sequences, ft_clear_command_sequence);
	else
		ft_lstclear(&shell_data->all_tokens, ft_clear_token);
	shell_data->all_tokens = NULL;
	shell_data->command_sequences = NULL;
}

void	ft_clear_command_sequence(void *node)
{
	t_command_sequences	*sequence;

	sequence = (t_command_sequences *)node;
	ft_free_pointer_and_set_to_null((void **)&sequence->command_path);
	ft_free_double_pointer_char(&sequence->envp_command_paths);
	if (sequence->args)
		ft_free_double_pointer_char(&sequence->args);
	ft_lstclear(&sequence->tokens, ft_clear_token);
	free(node);
}

void	ft_clear_token(void *node)
{
	t_tokens	*token;

	token = (t_tokens *)node;
	if (token->token)
		free(token->token);
	free(node);
}

void	ft_clear_env_variable(void *node)
{
	t_env	*env_variable;

	env_variable = (t_env *)node;
	ft_free_pointer_and_set_to_null((void **)&env_variable->name);
	ft_free_pointer_and_set_to_null((void **)&env_variable->value);
	free(node);
}