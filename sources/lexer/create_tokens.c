/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:48:01 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/11 20:15:38 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clear_contents_command_sequences(void *content)
{
	t_command_sequences	*command_sequences;

	command_sequences = (t_command_sequences *)content;
	if (command_sequences->sequence)
	{
		free(command_sequences->sequence);
		command_sequences->sequence = NULL;
	}
}

void 	ft_print_command_sequences(t_list *command_sequences)
{
	t_command_sequences	*one_sequence;

	while (command_sequences)
	{
		one_sequence = (t_command_sequences *)command_sequences->content;
		printf("one_sequence->command_sequence: %s\n", one_sequence->sequence);
		command_sequences = command_sequences->next;
	}
}


bool	ft_process_command_line(t_shell_data *shell_data)
{
	//printing the line read
	printf("command_line_read: %s\n\n", shell_data->command_line_read);
	//check for equal amount of quotes
	if (!ft_check_equal_quote_amt(shell_data->command_line_read))
		return (false);
	//create tokens for one command sequence
	if (!ft_create_tokens_for_sequence(shell_data->command_line_read, &shell_data->command_sequences))
	{
		printf("ft_create_tokens_for_sequence failed\n");
		return (false);
	}	



	// //create one command sequence (sepatated by pipes)
	// if (!ft_create_command_sequence(shell_data->command_line_read, &shell_data->command_sequences))
	// 	return (false);
	// //printing the command sequences
	// ft_print_command_sequences(shell_data->command_sequences);
	// //freeing the list of command sequences
	// ft_lstclear(&shell_data->command_sequences, ft_clear_contents_command_sequences);
	return (true);
}


bool	ft_create_tokens_for_sequence(char *command_line_read, t_list **command_sequences)
{
	char	*start;

	while (*command_line_read)
	{
		ft_skip_to_next_non_delimiter(&command_line_read);
		start = command_line_read;
		printf("Starting: %c\n", *command_line_read);
		ft_find_next_token(&command_line_read);
		printf("END: %c\n", *command_line_read);
		if (*command_line_read)
			command_line_read += 1;
	}
	return (true);
}

void	ft_skip_to_next_non_delimiter(char **command_line)
{
	while (**command_line == '\t' || **command_line == ' ')
		*command_line += 1;
}

bool	ft_find_next_token(char **string)
{
	int len;

	while (**string)
	{
		ft_skip_quote_block(string);
		if (**string == '|')
		{
			//finish this process and start reading for input and the continue with the new input
			printf("finishd one sequence\n");
		}
		if (**string == '<' || **string == '>')
		{
			printf("found redirection\n");
			ft_move_while_same_char(string, &len, **string);
		}
		if (**string)
		{
			printf("Inbetween: %c\n", **string);
			*string += 1;
		}
	}
	return (true);
}


//skips a block of chars which is inbetween two quotes of the same type.
void	ft_skip_quote_block(char **string)
{
	char	quote;

	while (**string == '\'' || **string == '\"')
	{
		quote = '\"';
		if (**string == '\'')
			quote = '\'';
		while (++(**string) && **string != quote)
			;
		if (**string && **string == quote)
			*string += 1;
	}
}


void	ft_move_while_same_char(char **command_line, int *len, char c)
{
	int	count;

	count = 0;
	while (**command_line == c)
	{
		count++;
		*command_line += 1;
	}
	if (len)
		*len = count; 
}

bool	ft_create_one_token(char *start, char *end, t_list **tokens)
{
	t_tokens	*token;
	int			len;
	char		*string;

	len = end - start;
	string = ft_substr(start, 0, len);
	if (!string)
	{
		//think about where to clear the things
		return (perror("error creatin string for token"), false);
	}
	return (true);
}













bool	ft_create_command_sequence(char *command_line_read, t_list **command_sequences)
{
	t_command_sequences	*one_sequence;
	t_list				*new_sequence;
	char				**splitted_by_pipe;
	int					i;

	i = 0;
	splitted_by_pipe = ft_split(command_line_read, '|');
	if(!splitted_by_pipe)
		return (perror("splitted_by_pipe - malloc error"), false);
	while (splitted_by_pipe[i])
	{
		one_sequence = ft_calloc(1, sizeof(t_command_sequences));
		if (!one_sequence)
		{
			ft_free_double_pointer_char(&splitted_by_pipe);
			return (perror("one_sequence - malloc error"), false);
		}
		one_sequence->sequence = splitted_by_pipe[i];
		new_sequence = ft_lstnew((void *)one_sequence);
		//free the everthing in the main function
		if (!new_sequence)
		{
			ft_free_double_pointer_char(&splitted_by_pipe);
			return (perror("new_sequence - malloc error"), false);
		}
		ft_lstadd_back(command_sequences, new_sequence);
		i++;
	}
	return (true);
}