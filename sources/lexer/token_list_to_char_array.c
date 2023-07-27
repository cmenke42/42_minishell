/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_to_char_array.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:23:48 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/27 19:11:31 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_token_list_to_args_array(t_command_sequences *one_sequence)
{
	t_tokens	*one_token;
	t_list		*tokens;
	int			i;

	i = 0;
	tokens = one_sequence->tokens;
	one_sequence->args = ft_calloc(ft_count_arguments(one_sequence->tokens) + 1, sizeof(char *));
	if (!one_sequence->args)
		return (perror("error creatin one_sequence->args"), false);
	while (tokens)
	{
		one_token = (t_tokens *)tokens->content;
		if (one_token->type == text)
		{
			ft_copy_token_from_list_to_array(one_sequence->args, &i, &one_token->token);
			i++;
		}
		tokens = tokens->next;
	}
	return (true);
}

int	ft_count_arguments(t_list *tokens)
{
	t_tokens	*one_token;
	int			number_of_arguments;

	number_of_arguments = 0;
	while (tokens)
	{
		one_token = (t_tokens *)tokens->content;
		if (one_token->type == text)
			number_of_arguments++;
		tokens = tokens->next;
	}
	return (number_of_arguments);
}

void	ft_copy_token_from_list_to_array(char **arguments, int *i, char **token)
{
	arguments[*i] = *token;
	*token = NULL;
}
