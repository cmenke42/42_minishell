/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 18:32:40 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/16 20:19:54 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_search_for_variable_expansion(t_shell_data *shell_data)
{
	t_list	*command_sequences;

	command_sequences = shell_data->command_sequences;
	while (command_sequences)
	{
		ft_expand_variable(((t_command_sequences *)command_sequences->content)->tokens);
		command_sequences = command_sequences->next;
	}
	return (true);
}

bool	ft_expand_variable(t_list *tokens)
{
	while (tokens)
	{
		if (!ft_do_variable_expansion((t_tokens *)tokens->content))
		{
			printf("some error with the expansion\n");
			return (false);
		}
		tokens = tokens->next;
	}
	return (true);
}

bool	ft_do_variable_expansion(t_tokens *token)
{
	ft_get_variable_name(token->token);
	return (true);
}

char	*ft_get_variable_name(char *string)
{
	char	*variable_name;

	int	i;

	i = 0;
	variable_name = NULL;
	while (*string)
	{
		if (*string == '$')
			ft_execute_specific_case_of_variable_expansion(&string, false, false);
		string += 1;
	}
	return (variable_name);
}

bool	ft_execute_specific_case_of_variable_expansion(char	**string, bool in_single_quotes, bool in_double_quotes)
{

	//keep the dollar sign
	// $ \0     $\t  \0 || '$' || "$''" "$""" || $\0
	if (ft_is_whitespace(*(*string + 1)) || in_single_quotes
		|| (in_double_quotes && ft_is_next_char_quote(*(*string + 1))) || !*(*string + 1))
			printf("keep the dollar\n");
	//remove the dollar sign
	// $"abc"  $'abc'
	else if (!in_single_quotes && !in_double_quotes && ft_is_next_char_quote(*(*string + 1)))
		printf("remove the goddam $\n");
	//replace with value
	else if (in_double_quotes)
		printf("replace with value\n");
	//replace with trimmed value
	else
		printf("replace with trimmed value\n");
	return (true);
}

bool	ft_is_next_char_quote(char c)
{
	return (c == '\'' || c == '\"');
}