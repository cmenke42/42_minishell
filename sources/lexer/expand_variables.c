/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 18:32:40 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/16 21:56:21 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_search_for_variable_expansion(t_shell_data *shell_data)
{
	t_list	*command_sequences;

	command_sequences = shell_data->command_sequences;
	while (command_sequences)
	{
		if (!ft_expand_variable(((t_command_sequences *)command_sequences->content)->tokens))
		{
			printf("error expanding variables\n");
			return (false);
		}
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
	char	**string;

	string = &token->token;
	//determine wheter the $ is in single, double or no quotes
	while (**string)
	{
		if (**string == '$')
			ft_execute_specific_case_of_variable_expansion(string, token->token, false, false);
		*string += 1;
	}
	return (true);
}

bool	ft_execute_specific_case_of_variable_expansion(char	**string, char *start, bool in_single_quotes, bool in_double_quotes)
{

	char *variable_name;

	variable_name = NULL;
	//keep the dollar sign
	// $ \0     $\t  \0 || '$' || "$''" "$""" || $\0
	if (ft_is_whitespace(*(*string + 1)) || in_single_quotes
		|| (in_double_quotes && ft_is_char_quote(*(*string + 1))) || !*(*string + 1))
	{
		printf("keep the dollar\n");
		return (true);
	}
	//remove the dollar sign
	// $"abc"  $'abc'
	else if (!in_single_quotes && !in_double_quotes && ft_is_char_quote(*(*string + 1)))
		printf("remove the goddam $\n");
	//PID speacial variable $$
	else if ((*(*string + 1)) == '$')
		printf("replace with PID of the current shell or script."); //or what else to with it
	//replace with value
	else if (in_double_quotes)
	{
		printf("replace with value\n");
		if (!ft_get_variable_name(*string, &variable_name))
			return (false);
	}
	//replace with trimmed value
	else
	{
		printf("replace with trimmed value\n");
		if (!ft_get_variable_name(*string, &variable_name))
			return (false);
	}
	return (true);
}

bool	ft_is_char_quote(char c)
{
	return (c == '\'' || c == '\"');
}

bool	ft_get_variable_name(char *string, char **variable_name)
{
	int		i;

	//1 to skip dollar at start
	i = 1;
	while (string[i] && string[i] != '$' && !ft_is_char_quote(string[i]) && !ft_is_whitespace(string[i]))
		i++;
	//start at 1 && len -1 for the dollar removal
	*variable_name = ft_substr(string, 1, (&string[i] - string) - 1);
	if (!variable_name)
		return (perror("error creating variable_name"), false);
	return (true);
}

char	*ft_get_variable_value(char	*variable_name)
{
	//search in the env list for the variable
		//if found retourn the string; -> do not free when using string_join later in replacement
		//else retourn NULL
	return ("  -    TEXT       -     ");
}

bool	ft_replace_variable_name_with_value(char **string, char *start, char *name, char *value)
{
	//dont free the value
	char	*result;
	int		value_len;
	int		result_len;

	value_len = 0;
	if (value)
		value_len = ft_strlen(value);
	result_len = ft_strlen(name) + (ft_strlen(start) - ft_strlen(*string)) - ft_strlen(name);
	result = malloc((result_len + 1) * sizeof(char));
	if (!result)
		return(perror("error creating new string with variable value"), false);
	while (*start)
	{
		if (start == *string)
		{
			start += ft_strlen(name) + 1; //for the $ + 1
			while (*value)
			{
				ft_assign_char_to_new_string(&result, *value);
				value += 1;
			}
		}
		else
			ft_assign_char_to_new_string(&result, *start);
		start += 1;
	}
}

void	ft_assign_char_to_new_string(char **new_string, char c)
{
	**new_string = c;
}