/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:48:01 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/18 18:57:29 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_process_command_line(t_shell_data *shell_data)
{
	//printing the line read
	printf("command_line_read: %s\n\n", shell_data->command_line_read);
	//check for equal amount of quotes
	if (!ft_check_equal_quote_amt(shell_data->command_line_read))
		return (false);
	//create tokens for one command sequence
	if (!ft_create_tokens_for_sequence(shell_data->command_line_read, &shell_data->all_tokens))
	{
		printf("ft_create_tokens_for_sequence failed\n");
		return (false);
	}
	// ft_print_token_list(shell_data->all_tokens);
	if (ft_is_syntax_error(shell_data))
	{
		printf("having a syntax error");
		return (false);
	}
	printf("\nstarting to split tokens in sequences\n\n");
	ft_split_tokens_in_sequences(shell_data);
	ft_print_command_sequences(shell_data->command_sequences);
	ft_search_for_variable_expansion(shell_data);
	// ft_lstclear(&shell_data->all_tokens, ft_clear_token);

	// loop_in_command_seq(shell_data);
	printf("\nhandling redirection\n\n");
	ft_handle_redirection_in_sequences(shell_data->command_sequences);

	// //create one command sequence (sepatated by pipes)
	// if (!ft_create_command_sequence(shell_data->command_line_read, &shell_data->command_sequences))
	// 	return (false);
	// //printing the command sequences
	// ft_print_command_sequences(shell_data->command_sequences);
	// //freeing the list of command sequences
	// ft_lstclear(&shell_data->command_sequences, ft_clear_command_sequence);
	shell_data->all_tokens = NULL;
	shell_data->command_sequences = NULL;
	return (true);
}



//printg the token list
void	ft_print_token_list(t_list *tokens)
{
	t_tokens	*token;

	while (tokens)
	{
		token = (t_tokens *)tokens->content;
		printf("token->token:%s\n", token->token);
		tokens = tokens->next;
	}
}

void	ft_print_command_sequences(t_list *command_sequences)
{
	t_command_sequences	*one_sequence;
	int i;

	i = 0;
	while (command_sequences)
	{
		printf("\nSequence %d\n", i++);
		one_sequence = (t_command_sequences *)command_sequences->content;
		ft_print_token_list(one_sequence->tokens);
		command_sequences = command_sequences->next;
	}
}

bool	ft_create_tokens_for_sequence(char *command_line_read, t_list **tokens)
{
	char				*start;
	//what need to happen when there is a newline in the command line read?
	while (*command_line_read)
	{
		ft_skip_to_next_non_delimiter(&command_line_read);
		start = command_line_read;
		// printf("Starting: %c\n", *command_line_read);
		ft_find_next_token(&command_line_read, &start, tokens);
		//creates one token if the string would be at least 1
		if (start != command_line_read && !ft_create_one_token(start, command_line_read, tokens))
			return (false); //check what needs to be cleared
		// printf("END: %c\n", *command_line_read);
		// if (*command_line_read && *command_line_read != '\"' && *command_line_read != '\'')
		// 	command_line_read += 1;
	}
	ft_print_token_list(*tokens);
	return (true);
}


void	ft_skip_to_next_non_delimiter(char **command_line)
{
	while (ft_is_whitespace(**command_line))
		*command_line += 1;
}

bool	ft_is_whitespace(char c)
{
	return (c == '\t' || c == ' ');
}

//seaparates the string by spaces and opeartors
bool	ft_find_next_token(char **string, char **start, t_list **tokens)
{
	while (**string)
	{
		ft_skip_quote_block(string, false);
		if (**string == '<' || **string == '>' || **string == '|')
		{
			if (*start != *string)
			{
				if (!ft_create_one_token(*start, *string, tokens))
					return (false); //check what needs to be cleared#
				printf("char: %c\n", **string);
				*start = *string;
			}
			// printf("found redirection\n");
			ft_move_while_same_char(string, **string);
			break ;
		}
		if (**string == ' ' || **string == '\t') //add newline???
			break;
		if (**string)
		{
			// printf("Inbetween: %c\n", **string);
			*string += 1;
		}
	}
	return (true);
}


void	ft_skip_quote_block(char **string, bool	only_single_quotes)
{
	char	quote;

	while (**string == '\'' || (!only_single_quotes && **string == '\"'))
	{
		quote = '\'';
		if (**string == '\"' && !only_single_quotes)
			quote = '\"';
		while (++(*string) && **string != quote)
			;
		if (**string && **string == quote)
			*string += 1;
	}
}

void	ft_move_while_same_char(char **command_line, char c)
{
	while (**command_line == c)
		*command_line += 1;
}

bool	ft_create_one_token(char *start, char *end, t_list **tokens)
{
	t_tokens	*token;
	t_list		*new_node;
	int			len;
	char		*string;

	token = ft_calloc(1, sizeof(t_tokens));
	if (!token)
	{
		ft_lstclear(tokens, ft_clear_token);
		return (false);
	}
	len = end - start;
	string = ft_substr(start, 0, len);
	printf("string: %s\n", string);
	if (!string)
	{
		//think about where to clear the things
		ft_lstclear(tokens, ft_clear_token);
		return (perror("error creatin string for token"), false);
	}
	token->token = string;
	new_node = ft_lstnew((void *)token);
	if (!new_node)
	{
		ft_lstclear(tokens, ft_clear_token);
		free(string);
		return (false);
	}
	ft_lstadd_back(tokens, new_node);
	return (true);
}
