/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:29:42 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/20 09:52:32 by wmoughar         ###   ########.fr       */
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
		if (one_token->type >= 3 && one_token->type <= 6)
		{
			if(!ft_do_redirection(&one_sequence->input_fd, &one_sequence->output_fd, one_token->type, next_token))
				return (false);
		}
		else if (next_token->type == text && !ft_remove_quotes_from_token(&next_token->token))
			return (false);
		tokens = tokens->next;
	}
	return (true);
}

bool	ft_do_redirection(int *input_fd, int *output_fd, char operator, t_tokens *file_token)
{
	if (operator == redirection_in || operator == redirection_in_heredoc)
		return(ft_input_redirection(input_fd, operator, file_token));
	else if (operator == redirection_out_trunc || operator == redirection_out_append)
		return (ft_output_redirection(output_fd, operator, file_token));
	return (true);
}

bool	ft_output_redirection(int *output_fd, char operator, t_tokens *file_token)
{
	int		fd;

	fd = 1;
	if (operator == redirection_out_trunc)
		fd = open(file_token->token, O_WRONLY | O_TRUNC | O_CREAT, RW_R__R__);
	else if (operator == redirection_out_append)
		fd = open(file_token->token, O_WRONLY | O_APPEND | O_CREAT, RW_R__R__);
	if (*output_fd != 1)
		close(*output_fd);
	file_token->type = redirection_filename;
	if (fd == -1)
		return (perror(file_token->token), false);
	*output_fd = fd;
	return (true);
}

bool	ft_input_redirection(int *input_fd, char operator, t_tokens *file_token)
{
	int fd;

	fd = 0;
	if (operator == redirection_in)
		fd = open(file_token->token, O_RDONLY);
	else if (operator == redirection_in_heredoc)
		create_heredoc(file_token);
	if (*input_fd != 0)
		close(*input_fd);
	if (fd == -1)
		return (perror(file_token->token), false);
	file_token->type = redirection_filename;
	*input_fd = fd;
	return (true);
}