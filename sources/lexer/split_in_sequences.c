/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_sequences.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:59:06 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/14 13:37:43 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_split_tokens_in_sequences(t_shell_data *shell_data)
{
	t_list				*tokens;
	t_list				*start_of_sequence;

	tokens = shell_data->all_tokens;
	start_of_sequence = shell_data->all_tokens;
	while (tokens)
	{
		if (!tokens->next || ft_find_pipe_operator(&tokens))
		{
			if (!ft_assing_tokens_to_sequence(start_of_sequence, &shell_data->command_sequences))
			{
				//maybe free something
				return (false);
			}
			if (!tokens)
				break;
			start_of_sequence = tokens;
			printf("\nstart of  sequeneve after cutting\n\n");
			ft_print_token_list(start_of_sequence);
			printf("\n\n");
		}
		else
			tokens = tokens->next;
	}
	return (true);
}

bool	ft_find_pipe_operator(t_list **tokens)
{
	t_tokens	*token;
	t_tokens	*next_token;
	t_list		*next_token_node;

	while ((*tokens)->next)
	{
		token = (t_tokens *)((*tokens)->content);
		next_token_node = (*tokens)->next;
		next_token = (t_tokens *)next_token_node->content;
		if (next_token->type == pipe_operator)
		{
			ft_cut_out_pipe_node(tokens, next_token_node);
			return (true);
		}
		*tokens = (*tokens)->next;
	}
	return (false);
}

void	ft_cut_out_pipe_node(t_list **tokens, t_list *next_token_node)
{
	(*tokens)->next = NULL;
	(*tokens) = next_token_node->next;
	ft_lstdelone(next_token_node, ft_clear_token);
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
