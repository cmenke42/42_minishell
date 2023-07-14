/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_sequences.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:59:06 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/14 11:50:53 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_split_tokens_in_sequences(t_shell_data *shell_data)
{
	t_list				*tokens;
	t_list				*next_token_node;
	t_list				*start_of_sequence;
	t_tokens			*next_token;

	tokens = shell_data->all_tokens;
	start_of_sequence = shell_data->all_tokens;
	ft_print_token_list(tokens);
	while (tokens->next)
	{
		next_token_node = tokens->next;
		next_token = (t_tokens *)next_token_node->content;
		if (next_token->type == pipe_operator)
		{
			ft_assing_tokens_to_sequence(start_of_sequence);
			tokens->next = NULL;
			tokens = next_token_node->next;
			// ft_print_token_list(start_of_sequence);
			start_of_sequence = next_token_node->next;
			ft_lstdelone(next_token_node, ft_clear_token);
		}
		else
			tokens = tokens->next;
	}
	return (true);
}

bool	ft_assing_tokens_to_sequence(t_list *start_of_sequence)
{
	t_command_sequences	*one_sequence;
	t_list				*new_sequence_node;

	printf("\nOne sequence:\n\n");
	return (true);
}

//preapare
//create node to store the contents

//read the tokens and process the input
	//check for redirection and remove the nodes from the list -> stop at an error in this sequence
	//check for the first text node -> command
	//then check for 