/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:46:20 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/26 21:10:23 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_print_pipe_fds(int **pipe_fds, int number_of_pipes)
{
	int	i;

	i = 0;
	while (i < number_of_pipes)
	{
		printf("pipe_fds[%d][0] = %d\n", i, pipe_fds[i][0]);
		printf("pipe_fds[%d][1] = %d\n", i, pipe_fds[i][1]);
		i++;
	}
}

void	ft_print_envp_array(char **envp_array)
{
	int	i;

	i = 0;
	while (envp_array[i])
	{
		ft_putstr_fd("envp_array: ", 2);
		ft_putstr_fd(envp_array[i], 2);
		ft_putendl_fd("", 2);
		i++;
	}
}

void	ft_print_double_pointer(char **string)
{
	int i;
	
	i = 0;
	while (string && string[i])
		printf("%s\n", string[i++]);
}

void	ft_print_command_sequences_args(t_list *command_sequences)
{
	t_command_sequences	*one_sequence;
	int i;

	i = 0;
	while (command_sequences)
	{
		printf("\nSequence %d\n", i++);
		one_sequence = (t_command_sequences *)command_sequences->content;
		ft_print_double_array(one_sequence->args);
		command_sequences = command_sequences->next;
	}
}


void	ft_print_double_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		printf("array[%d]: %s\n", i, array[i]);
		i++;
	}
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

const char* token_enum_to_string[][2] =
{
{"text", "0"},
{"syntax_error", "1"},
{"pipe_operator", "2"},
{"redirection_in", "3"},
{"redirection_in_heredoc", "4"},
{"redirection_out_trunc", "5"},
{"redirection_out_append", "6"},
{"redirection_filename", "7"} //remove this while thing
};

void ft_print_tokens_and_type(t_list *tokens)
{
	t_list		*temp;
	t_tokens	*token;


	temp = tokens;
	while (temp)
	{
		token = (t_tokens *)temp->content;
		ft_printf(BOLD_YELLOW"token:"STYLE_DEF"%s		"BOLD_PINK"type:"STYLE_DEF"%s\n", token->token, token_enum_to_string[(int)token->type][0]);
		temp = temp->next;
	}
	return ;
}

void	ft_print_env_list(t_list *env_list)
{
	t_env	*env_variable;

	while (env_list)
	{
		env_variable = (t_env *)env_list->content;
		printf("%s=%s\n", env_variable->name, env_variable->value);
		env_list = env_list->next;
	}
}