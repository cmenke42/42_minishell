/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:29:42 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/25 17:49:38 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_handle_here_doc_operator(t_list *command_sequences)
{
	t_command_sequences	*one_sequence;
	int i;

	i = 0;
	while (command_sequences)
	{
		one_sequence = (t_command_sequences *)command_sequences->content;
		if (!ft_create_and_save_heredocs(one_sequence->tokens, &i))
			return (false);
		command_sequences = command_sequences->next;
	}
	return (true);
}

bool	ft_handle_redirection_operators(t_command_sequences *one_sequence, t_list *tokens_of_sequence)
{
	t_tokens	*one_token;
	t_tokens	*next_token;

	if (one_sequence->output_fd == 0)
		one_sequence->output_fd = 1;
	if (ft_lstsize(tokens_of_sequence) == 1 && !ft_remove_quotes_from_token(&((t_tokens *)tokens_of_sequence->content)->token))
		return (false);
	while (tokens_of_sequence->next)
	{
		one_token = (t_tokens *)tokens_of_sequence->content;
		next_token = (t_tokens *)tokens_of_sequence->next->content;
		if (one_token->type >= 3 && one_token->type <= 6)
		{
			if (next_token->type == text && !ft_remove_quotes_from_token(&next_token->token))
				return (false);
			if(!ft_do_redirection(&one_sequence->input_fd, &one_sequence->output_fd, one_token->type, next_token))
				return (false);
		}
		tokens_of_sequence = tokens_of_sequence->next;
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
	if (*output_fd > 1)
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
	if (*input_fd > 0)
		close(*input_fd);
	if (fd == -1)
		return (perror(file_token->token), false);
	file_token->type = redirection_filename;
	*input_fd = fd;
	return (true);
}