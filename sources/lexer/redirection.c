/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:29:42 by wmoughar          #+#    #+#             */
/*   Updated: 2023/08/01 23:16:41 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_handle_redirection_operators(t_command_sequences *one_sequence, t_list *tokens_of_sequence, t_shell_data *shell_data)
{
	t_tokens	*one_token;
	t_tokens	*next_token;

	if (one_sequence->output_fd == 0)
		one_sequence->output_fd = 1;
	while (tokens_of_sequence->next)
	{
		one_token = (t_tokens *)tokens_of_sequence->content;
		next_token = (t_tokens *)tokens_of_sequence->next->content;
		if (!ft_remove_quotes_from_string(&one_token->token))
			return (__system_call_error);
		if (one_token->type >= 3 && one_token->type <= 6)
		{
			if (!ft_remove_quotes_from_string(&next_token->token))
				return (__system_call_error);
			if(ft_do_redirection(one_sequence, one_token, next_token, shell_data) == __stop_execution)
				return (__stop_execution);
			tokens_of_sequence = tokens_of_sequence->next->next;
		}
		else
			tokens_of_sequence = tokens_of_sequence->next;
		if(!tokens_of_sequence)
			break ;
	}
	if (tokens_of_sequence)
	{
		one_token = (t_tokens *)tokens_of_sequence->content;
		if (!ft_remove_quotes_from_string(&one_token->token))
			return (__system_call_error);
	}
	return (__success);
}

int	ft_do_redirection(t_command_sequences *one_sequence, t_tokens *operator_token, t_tokens *file_token, t_shell_data *shell_data)
{
	if (operator_token->type == redirection_in || operator_token->type == redirection_in_heredoc)
		return(ft_input_redirection(&one_sequence->input_fd, operator_token, file_token, shell_data));
	else if (operator_token->type == redirection_out_trunc || operator_token->type == redirection_out_append)
		return (ft_output_redirection(&one_sequence->output_fd, operator_token->type, file_token));
	return (__success);
}

int	ft_output_redirection(int *output_fd, char operator, t_tokens *file_token)
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
		return (ft_put_redirection_error(file_token->token), __stop_execution);
	*output_fd = fd;
	return (__success);
}

int	ft_input_redirection(int *input_fd, t_tokens *operator_token, t_tokens *file_token, t_shell_data *shell_data)
{
	int fd;

	fd = 0;
	if (operator_token->type == redirection_in)
		fd = open(file_token->token, O_RDONLY);
	else if (operator_token->type == redirection_in_heredoc)
		fd = open(shell_data->heredocs[operator_token->heredoc_number], O_RDONLY);
	if (*input_fd > 0)
		close(*input_fd);
	if (fd == -1)
		return (ft_put_redirection_error(file_token->token), __stop_execution);
	file_token->type = redirection_filename;
	*input_fd = fd;
	return (__success);
}

void	ft_put_redirection_error(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	perror("");
}