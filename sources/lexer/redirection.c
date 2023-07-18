/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:29:42 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/18 17:54:58 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	print_and_append(t_tokens *file_token)
// {
// 	int	fd;

// 	fd = open(file_token->token, O_RDWR | O_CREAT | O_APPEND, 0644);
// 	ft_putendl_fd(token, fd);
// 	close(fd);
// }


//dup2(fd, stdout_fileno)
//close f

/*
	enter shell data
	while (command_sequences)
		while (tokens)
			if (token->type == redirection)
			{
				determine redirection and execute if possible
				{
					dup2(output_fd, STDOUT_FILENO)
					in output fd;
				}
			}
		tokens = tokens->next
	command_sequence = command_seq->next
*/
//token = (t_tokens *)((*tokens)->content);


void	append_print(int fd, char *filename)
{
	fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	ft_putendl_fd("sadajdka\n", fd);
	// dup2()
	// close(fd);
}

void loop_in_command_seq(t_shell_data *data)
{
	t_list *command_sequences = data->command_sequences;
	t_list *tokens;
	t_command_sequences *seq = (t_command_sequences *)(command_sequences->content);
	tokens = seq->tokens;
	while(seq)
	{
		seq = (t_command_sequences *)(command_sequences->content);
		while (tokens)
		{
			if (((t_tokens *)(tokens->content))->type == redirection_out_append)
			{
				append_print(seq->output_fd, ((t_tokens *)(tokens->next->content))->token);
			}
			tokens = tokens->next;
		}
		command_sequences = command_sequences->next;
	}
}