/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:50:59 by cmenke            #+#    #+#             */
/*   Updated: 2023/06/23 15:08:03 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_open_file_fds(char **argv, int files_fd[2])
{
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	files_fd[0] = open(argv[1], O_RDONLY);
	if (files_fd[0] == -1)
		perror("infile");
	files_fd[1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, mode);
	if (files_fd[1] == -1)
		perror("outfile");
}


bool	ft_open_file_append_trunc(char *file_name)
{
	int	fd;
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, mode);
	if (fd == -1)
	{
		perror("outfile");
		return (false);
	}
	return (true);
}

void	ft_skip_single_quotes(char *cmd_line, int *i)
{
	char	quote;

	while (cmd_line[*i] && cmd_line[*i] == '\'')
	{
		quote = '\'';
		while (cmd_line[++(*i)] && cmd_line[*i] != quote)
			;
		if (cmd_line[*i] && cmd_line[*i] == quote)
			*i += 1;
	}
}

void ft_skip_whitespace(char *string, int *i)
{
	while (string[*i] && (string[*i] == ' '
		|| string[*i] == '\t' || string[*i] == '\n'))
		*i += 1;
}

char	*ft_trim_variable_value(char *string)
{
	int		i;
	int		j;
	int		start;
	int		count;
	char	*result;

	i = 0;
	count = 0;
	while (string[i])
	{
		start = i;
		ft_skip_whitespace(string, &i);
		if (string[i] && start > 0 && start != i)
			count++;
		if (string[i])
		{
			count++;
			i++;
		}
	}
	result = malloc((count + 1) * sizeof(char));
	if (!result)
		return (result);
	i = 0;
	j = 0;
	printf("string: %s\n", string);
	while (string[i])
	{
		start = i;
		ft_skip_whitespace(string, &i);
		if (string[i] && start > 0 && start != i)
			result[j++] = ' ';
		if (string[i])
		{
			result[j++] = string[i];	
			i++;
		}
	}
	result[j] = '\0';
	// free(string);
	return (result);
}

bool	ft_expand_variable(t_tokens *token)
{
	//search for single quotes - skip block
	//seachr for double quotes - expand variable preserve spaces
	//search for $? - expand variable in place - ignore the rest of the text after ?
	//search for $ - expand variable in place - trim spaces
	char	*string;
	int		i;
	bool	in_double_quote;
	bool	valid;

	in_double_quote = false;
	valid = true;
	string = token->token;
	i = 0;
	// while (string[i])
	// {
	// 	if (string[i] == '\'')
	// 		ft_skip_single_quotes(string, &i);
	// 	if (string[i] == '\"' && in_double_quote == false)
	// 		in_double_quote = true;
	// 	else
	// 		in_double_quote = false;
	// 	if (string[i] == '$' && in_double_quote == false)
	// 		valid = ft_expand_variable_in_place(string, &i);
	// 	else if (string[i] == '$' && in_double_quote == true)
	// 		valid = ft_expand_variable_preserve_spaces(string, &i);
	// 	else
	// 		i++;
	// }
	while (string[i])
	{
		if (string[i] == '$' && (string[i + 1] == '\'' || string[i + 1] == '\"'))
			ft_remoove_dollar_sign(string, &i);
			valid = ft_expand_variable_in_place(string, &i);
		else if (string[i] == '$')
			valid = ft_expand_variable_preserve_spaces(string, &i);
		else
			i++;
		i++;
	}
	return (valid);
}

bool	ft_variable_expansion(t_data *data)
{

	t_tokens	*token;

	token = data->tokens;

}

bool	ft_handle_operators(t_data *data)
{
	//1. expand variables - assume like this -> variable in and value out
	//2. here_doc
	//3. redirection

}
