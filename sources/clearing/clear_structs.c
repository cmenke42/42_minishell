/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:08:25 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/23 18:35:09 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//in main programm

void	ft_free_shell_data_for_next_command(t_shell_data *shell_data)
{
	ft_free_pointer_and_set_to_null((void **)&shell_data->command_line_read);
	ft_free_double_pointer_char(&shell_data->envp_array);
	ft_free_pointer_and_set_to_null((void **)&shell_data->process_ids);
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
	if (sequence->args)
		ft_free_double_pointer_char(&sequence->args);
	else
		ft_clear_token((void *)sequence->tokens);
	free(node);
}

void	ft_clear_token(void *token)
{
	t_tokens	*node;

	node = (t_tokens *)token;
	if (node)
	{
		if (node->token)
			free(node->token);
		free(node);
	}
}