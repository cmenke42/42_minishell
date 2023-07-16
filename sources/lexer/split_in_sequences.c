/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_sequences.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:59:06 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/16 17:33:12 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_split_tokens_in_sequences(t_shell_data *shell_data)
{
	t_list				*tokens;
	t_list				*start_of_sequence;
	bool				pipe_inside;

	tokens = shell_data->all_tokens;
	start_of_sequence = shell_data->all_tokens;
	pipe_inside = true;
	while (tokens)
	{
		if (pipe_inside)
			pipe_inside = ft_find_pipe_operator(&tokens);
		if (pipe_inside || !tokens)
		{
			if (!ft_assing_tokens_to_sequence(start_of_sequence, &shell_data->command_sequences))
			{
				//maybe free something
				return (false);
			}
			start_of_sequence = tokens;
		}
		else if (tokens)
			tokens = tokens->next;
	}
	return (true);
}

bool	ft_find_pipe_operator(t_list **tokens)
{
	t_tokens	*token;
	t_list		*previous_token_node;

	previous_token_node = NULL;
	while (*tokens)
	{
		token = (t_tokens *)((*tokens)->content);
		if (token->type == pipe_operator)
		{
			ft_cut_out_pipe_node(tokens, previous_token_node);
			return (true);
		}
		previous_token_node = *tokens;
		if (*tokens)
			*tokens = (*tokens)->next;
	}
	return (false);
}

void	ft_cut_out_pipe_node(t_list **tokens, t_list *previous_token_node)
{
	t_list	*temp;

	temp = *tokens;
	if (previous_token_node)
		previous_token_node->next = NULL;
	*tokens = (*tokens)->next;
	ft_lstdelone(temp, ft_clear_token);
}

bool	ft_assing_tokens_to_sequence(t_list *start_of_sequence, t_list **command_sequences)
{
	t_command_sequences	*one_sequence;
	t_list				*new_sequence_node;

	one_sequence = ft_calloc(1, sizeof(t_command_sequences));
	if (!one_sequence)
	{
		ft_lstclear(&start_of_sequence, ft_clear_token);
		perror("error creating one_sequence node");
		return (false);
	}
	new_sequence_node = ft_lstnew((void *)one_sequence);
	if (!new_sequence_node)
	{
		free(one_sequence);
		ft_lstclear(&start_of_sequence, ft_clear_token);
		perror("error creating one_sequence node");
		return (false);
	}
	one_sequence->tokens = start_of_sequence;
	ft_lstadd_back(command_sequences, new_sequence_node);
	return (true);
}

//preapare
//create node to store the contents

//read the tokens and process the input
	//check for redirection and remove the nodes from the list -> stop at an error in this sequence
	//check for the first text node -> command
	//then check for 
