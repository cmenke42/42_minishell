/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 18:32:40 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/01 12:08:20 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// bool	ft_search_for_variable_expansion(t_shell_data *shell_data)
// {
// 	t_list	*command_sequences;

// 	command_sequences = shell_data->command_sequences;
// 	while (command_sequences)
// 	{
// 		if (!ft_expand_variable(((t_command_sequences *)command_sequences->content)->tokens, shell_data))
// 		{
// 			printf("error expanding variables\n");
// 			return (false);
// 		}
// 		command_sequences = command_sequences->next;
// 	}
// 	return (true);
// }

bool	ft_expand_variables(t_list *tokens, t_shell_data *shell_data)
{
	t_list		*previous_token_node;

	previous_token_node = NULL;
	while (tokens)
	{
		//free the variable name
		if (!ft_strcmp(((t_tokens *)tokens->content)->token, ""))
			tokens = tokens->next;
		else
		{
			if (!ft_do_variable_expansion((t_tokens *)tokens->content, shell_data))
			{
				ft_putendl_fd("some error with the expansion", 2);
				return (false);
			}
			if (!ft_strcmp(((t_tokens *)tokens->content)->token, ""))
			{
				if (tokens == shell_data->all_tokens)
					shell_data->all_tokens = tokens->next;
				ft_cut_out_empty_node(&tokens, previous_token_node);
			}
			previous_token_node = tokens;
			if (tokens)
				tokens = tokens->next;
		}
	}
	return (true);
}

bool	ft_do_variable_expansion(t_tokens *token, t_shell_data *shell_data)
{
	char	*string;
	bool	in_double_quotes;
	bool	in_single_quotes;

	string = token->token;
	in_double_quotes = false;
	in_single_quotes = false;
	//determine wheter the $ is in single, double or no quotes
	while (*string)
	{
		if (!in_single_quotes && !in_double_quotes && *string == '\'')
			in_single_quotes = true;
		else if (in_single_quotes && *string == '\'')
			in_single_quotes = false;
		if (!in_double_quotes && !in_single_quotes && *string == '\"')
			in_double_quotes = true;
		else if (in_double_quotes && !in_single_quotes && *string == '\"')
			in_double_quotes = false;
		if (*string == '$' && !in_single_quotes)
		{
			if (!ft_execute_specific_case_of_variable_expansion(&string, &token->token, in_double_quotes, shell_data))
				return (false); //maybe clear something
		}
		else
			string += 1;
	}
	return (true);
}

//string starts at the $
bool	ft_execute_specific_case_of_variable_expansion(char	**string, char **token, bool in_double_quotes, t_shell_data *shell_data)
{
	char	*variable_name;
	char	*trimmed;
	char	*value;
	char	*exit_code;

	variable_name = NULL;
	value = NULL;
	//keep the dollar sign
	// $ \0     $\t  \0 || '$' || "$''" "$""" || $\0
	if (ft_is_whitespace(*(*string + 1))
		|| (in_double_quotes && ft_is_char_quote(*(*string + 1))) || !*(*string + 1))
	{
		// printf("keep the dollar\n");
		*string += 1;
		return (true);
	}
	//remove the dollar sign
	// $"abc"  $'abc'
	else if (!in_double_quotes && ft_is_char_quote(*(*string + 1)))
	{
		// printf("remove the goddam $\n");
		if (!ft_replace_variable_name_with_value(string, token, NULL, NULL))
			return (false);
	}
	//keep the $$ -> getpid is forbidden
	else if ((*(*string + 1)) == '$')
	{
		*string += 1;
		return (true); 
	}
	//exit code $?
	else if ((*(*string + 1)) == '?')
	{
		// printf("replace with PID of the current shell or script.\n"); //or what else to with it
		// free the process_id
		if (g_signal_number != 0)
		{
			shell_data->exit_code = g_signal_number + 128;// check which value it should have
			g_signal_number = 0;
		}
		exit_code = ft_itoa(shell_data->exit_code);
		if (!exit_code)
			return (false);
		// printf("PID:%s", process_id);
		if (!ft_replace_variable_name_with_value(string, token, NULL, exit_code))
			return (false);
	}
	//replace with value
	else if (in_double_quotes)
	{
		// printf("replace with value\n");
		if (!ft_get_variable_name(*string, &variable_name))
			return (false);
		if (!ft_replace_variable_name_with_value(string, token, variable_name, ft_get_variable_value(shell_data->env_list, variable_name)))
			return (false);
	}
	//replace with trimmed value
	else //if !in_double quotes
	{
		// printf("replace with trimmed value\n");
		if (!ft_get_variable_name(*string, &variable_name))
			return (false);
		// printf("variable_name:%s\n", variable_name);
		// Trim the value if needed in the get value funciton
		value = ft_get_variable_value(shell_data->env_list, variable_name);
		trimmed = ft_trim_variable_value(value);
		// printf("TRIMMED VALUE: %s\n", trimmed);
		if (!ft_replace_variable_name_with_value(string, token, variable_name, trimmed))
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

char	*ft_get_variable_value(t_list *env_list, char *variable_name)
{
	//search in the env list for the variable
		//if found retourn the string; -> do not free when using string_join later in replacement
		//else retourn NULL
	t_list *variable_node;
    char *value;

	if(!variable_name)
		return (NULL);
	value = NULL;
	variable_node = ft_search_for_env_variable(variable_name, env_list);
    if (variable_node)
   		value = ((t_env *)variable_node->content)->value;
    return (value);
}

bool	ft_replace_variable_name_with_value(char **string, char **token, char *name, char *value)
{
	char	*first_part;
	char	*first_part_and_value;
	char	*last_part;
	char	*result;
	int		name_len;


	//for the $$ PID
	name_len = 1;
	if((*(*string + 1)) == '$' || (*(*string + 1)) == '?')
		name_len = 2;
	first_part = NULL;
	if (name)
	{
		name_len += ft_strlen(name);
		ft_free_pointer_and_set_to_null((void **)&name);
	}
	if (*string - *token > 0)
	{
		first_part = ft_substr(*token, 0, *string - *token);
		if (!first_part)
			return (false);
		// printf("first_part:%s\n", first_part);
	}
	if (first_part && value)
	{
		first_part_and_value = ft_strjoin(first_part, value);
		if (!first_part_and_value)
			return (false);
		// printf("first_part_and_value:%s\n", first_part_and_value);
	}
	//there are leaks!!!!!!!!1
	else if(!first_part)
		first_part_and_value = value;
	//printf("hello\n");
	// +1 for the $;
	last_part = ft_strdup(*string + name_len);
	if (!last_part)
	{
		if (first_part_and_value)
			free(first_part_and_value);
		if (first_part)
			free(first_part);
	}
	// printf("last_part:%s\n", last_part);
	if (value)
	{
		result = ft_strjoin(first_part_and_value, last_part);
		//free(first_part_and_value);
		free(last_part);
	}
	else if (!first_part)
	{
		result = last_part;
	}
	else
	{
		result = ft_strjoin(first_part, last_part);
		if (first_part)
			free(first_part);
		free(last_part);
	}
	if (!result)
		return (false);
	// printf("result: %s\n", result);
	free(*token);
	*token = result;
	*string = *token;
	return (true);
}

void	ft_cut_out_empty_node(t_list **tokens, t_list *previous_token_node)
{
	t_list	*temp;

	temp = *tokens;
	if (previous_token_node)
		previous_token_node->next = (*tokens)->next;
	*tokens = (*tokens)->next;
	ft_lstdelone(temp, ft_clear_token);
}