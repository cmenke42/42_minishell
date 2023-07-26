/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:07:55 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/26 17:13:52 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_create_and_save_heredocs(t_list *tokens_of_sequence, int *i)
{
	t_tokens	*one_token;
	t_tokens	*next_token;
	char		*heredoc_filename;

	while (tokens_of_sequence->next)
	{
		one_token = (t_tokens *)tokens_of_sequence->content;
		next_token = (t_tokens *)tokens_of_sequence->next->content;
		if (one_token->type == redirection_in_heredoc)
		{
			heredoc_filename = create_heredoc(next_token, i); //delete files after or leave them??
			if (!heredoc_filename)
				return (false);
			free(next_token->token);
			next_token->token = heredoc_filename;
			one_token->type = redirection_in;
			*i += 1;
		}
		tokens_of_sequence = tokens_of_sequence->next;
	}
	return (true);
}

int	check_quotes(t_tokens *delimiter)
{
	int	i;

	i = 0;
	while (delimiter->token[i])
	{
		if (delimiter->token[i] == '\'' || delimiter->token[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

// char	*expand_line(char *line, t_env *env_list)
// {
// 	t_tokens	*token;
// 	char		*str;

// 	token = (t_tokens *)malloc(sizeof(t_tokens));
// 	if (!token)
// 		return (NULL);
// 	token->token = line;
// 	ft_expand_variable((t_tokens *)token, env_list);
// 	str = token->token;
// 	free(token);
// 	return (str);
// }

char	*create_heredoc(t_tokens *command, int *i)
{
	char	*line;
	int		heredoc_fd;
	char	*heredoc_filename;


	heredoc_fd = ft_create_heredoc_file(&heredoc_filename, i);
	if (heredoc_fd == -1)
		return (NULL);
	if (check_quotes(command))
		command->token = ft_remove_quotes_from_token(&command->token); //check for error return and adjust the function remove quotes
	while (1)
	{
		line = readline("> ");
		if (!line[0])
			continue ;
		if (!ft_strncmp(line, command->token, ft_strlen(line)))
			break ;
		ft_putendl_fd(line, heredoc_fd);
		free(line);
	}
	if (line)
		free(line);
	close(heredoc_fd);
	return (heredoc_filename);
}

int	ft_create_heredoc_file(char **heredoc_filename, int *i)
{
	char	*file_number;
	int 	heredoc_fd;

	file_number = ft_itoa(*i);
	if (!file_number)
		return (perror("error creating the file_number string"), -1);
	*heredoc_filename = ft_strjoin("heredocs/.heredoc_", file_number);
	free(file_number);
	if (!heredoc_filename)
		return (perror("error creating the herdoc_filename"), -1);
	heredoc_fd = open(*heredoc_filename, O_CREAT | O_RDWR | O_TRUNC, RW_R__R__);
	if (heredoc_fd == -1)
		perror("error creating the heredo_file");
	return (heredoc_fd);
}