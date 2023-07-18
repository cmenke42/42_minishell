/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:29:42 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/18 20:32:34 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// // void	print_and_append(t_tokens *file_token)
// // {
// // 	int	fd;

// // 	fd = open(file_token->token, O_RDWR | O_CREAT | O_APPEND, 0644);
// // 	ft_putendl_fd(token, fd);
// // 	close(fd);
// // }


// //dup2(fd, stdout_fileno)
// //close f

// /*
// 	enter shell data
// 	while (command_sequences)
// 		while (tokens)
// 			if (token->type == redirection)
// 			{
// 				determine redirection and execute if possible
// 				{
// 					dup2(output_fd, STDOUT_FILENO)
// 					in output fd;
// 				}
// 			}
// 		tokens = tokens->next
// 	command_sequence = command_seq->next
// */
// //token = (t_tokens *)((*tokens)->content);


// void	append_print(int fd, char *filename)
// {
// 	fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
// 	ft_putendl_fd("sadajdka\n", fd);
// 	// dup2()
// 	// close(fd);
// }

// void loop_in_command_seq(t_shell_data *data)
// {
// 	t_list *command_sequences = data->command_sequences;
// 	t_list *tokens;
// 	t_command_sequences *seq = (t_command_sequences *)(command_sequences->content);
// 	tokens = seq->tokens;
// 	while(seq)
// 	{
// 		seq = (t_command_sequences *)(command_sequences->content);
// 		while (tokens)
// 		{
// 			if (((t_tokens *)(tokens->content))->type == redirection_out_append)
// 			{
// 				append_print(seq->output_fd, ((t_tokens *)(tokens->next->content))->token);
// 			}
// 			tokens = tokens->next;
// 		}
// 		command_sequences = command_sequences->next;
// 	}
// }


bool	ft_handle_redirection_in_sequences(t_list *command_sequences)
{
	t_command_sequences	*one_sequence;

	while (command_sequences)
	{
		one_sequence = (t_command_sequences *)command_sequences->content;
		one_sequence->input_fd = 0;
		one_sequence->output_fd = 1;
		if(!ft_handle_redirection_in_tokens(one_sequence, one_sequence->tokens))
			return (false);
		command_sequences = command_sequences->next;
	}
	return (true);
}

bool	ft_handle_redirection_in_tokens(t_command_sequences *one_sequence, t_list *tokens)
{
	t_tokens	*one_token;
	t_tokens	*next_token;

	while (tokens->next)
	{
		one_token = (t_tokens *)tokens->content;
		next_token = (t_tokens *)tokens->next->content;
		if(!ft_do_redirection(one_sequence, one_token->type, next_token->token))
			return (false);

		tokens = tokens->next;
	}
	return (true);	
}

bool	ft_do_redirection(t_command_sequences *one_sequence, char operator, char *file)
{

	int fd;
	//what to do with multiple redirection in one sequene?
		//Keep the last one and close the rest
	if (operator == text)
		return (true);
	if (!ft_get_filedescriptor(&one_sequence->input_fd, &one_sequence->output_fd, operator, file))
		return (false);

		//check if there is already a fd in the node stored
			// if so then close it and place the new one there.
	return (true);
}

bool	ft_get_filedescriptor(int *input_fd, int *output_fd, char operator, char *file)
{
	if (operator == redirection_in || operator == redirection_in_heredoc)
		printf("input redirection\n");
	else if (operator == redirection_out_trunc || operator == redirection_out_append)
		return (ft_output_redirection(output_fd, operator, file));
}

bool	ft_output_redirection(int *output_fd, char operator, char *file)
{
	int		fd;

	if (operator == redirection_out_trunc)
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, RW_R__R__);
	else if (operator == redirection_out_append)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, RW_R__R__);
	if (*output_fd != 1)
		close(*output_fd);
	if (fd == -1)
		return (perror(file), false);
	*output_fd = fd;
	return (true);
}

bool	ft_input_redirection(int *input_fd, char operator, char *file)
{
	int fd;

	if (operator == redirection_in)
		fd = open(file, O_RDONLY);
	else if (operator == redirection_in_heredoc)
		prinf("do herdeco\n");
	if (*input_fd != 0)
		close(input_fd);
	if (fd == -1)
		return (perror(file), false);
	*input_fd = fd;
	return (true);
}