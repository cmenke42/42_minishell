/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:07:55 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/28 21:08:12 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_handle_heredocs(t_shell_data *shell_data)
{
	int status;

	if (!ft_create_heredoc_names(shell_data))
		return (__system_call_error);
	status = ft_read_heredocs_in_child_process(shell_data);
	return (status);
}

int	ft_read_heredocs_in_child_process(t_shell_data *shell_data)
{
	pid_t	process_id;
	int 	stat_loc;
	int		exit_code;

	stat_loc = 0;
	exit_code = 0;
	process_id = fork();
	if (process_id == -1)
		return (perror("error fork for heredoc"), false);
	if (process_id == 0)
		ft_open_reading_for_heredocs(shell_data->all_tokens, shell_data->heredocs);
	signal(SIGINT, ft_sig_sigint_handler_parent_execution);
	waitpid(process_id, &stat_loc, 0);
	ft_get_exit_code(&exit_code, stat_loc, true);
	ft_set_minisell_signals();
	if (exit_code == 1)
		return (__system_call_error);
	else if (exit_code > 1)
		return (__stop_execution);
	return (__success);
}

bool	ft_open_reading_for_heredocs(t_list *tokens, char **heredocs)
{
	t_tokens	*one_token;
	t_tokens	*next_token;
	int			i;

	signal(SIGINT, SIG_DFL);
	i = 0;
	while (tokens->next)
	{
		one_token = (t_tokens *)tokens->content;
		next_token = (t_tokens *)tokens->next->content;
		if (one_token->type == redirection_in_heredoc)
		{
			if (!ft_fill_heredoc(heredocs[i], next_token->token))
				exit(1);//free_data
			i++;
		}
		tokens = tokens->next;
	}
	exit(0); //free_data
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

bool	ft_create_heredoc_names(t_shell_data *shell_data)
{
	int	number_of_heredocs;
	int	i;

	i = 0;
	number_of_heredocs = ft_count_heredocs(shell_data->all_tokens);
	if (number_of_heredocs == 0)
		return (true);
	shell_data->heredocs = ft_calloc(number_of_heredocs + 1, sizeof(char *));
	if (!shell_data->heredocs)
		return (perror("error creating shell_data->heredocs"), false);
	while (i < number_of_heredocs)
	{
		shell_data->heredocs[i] = ft_create_here_doc_name(i);
		if (!shell_data->heredocs[i])
			return (false);
		i++;
	}
	return (true);
}

int	ft_count_heredocs(t_list *tokens)
{
	t_tokens	*one_token;
	int			i;

	i = 0;
	while (tokens)
	{
		one_token = (t_tokens *)tokens->content;
		if (one_token->type == redirection_in_heredoc)
			i++;
		tokens = tokens->next;
	}
	return (i);
}

char	*ft_create_here_doc_name(int i)
{
	char	*file_number;
	char	*heredoc_filename;

	heredoc_filename = NULL;
	file_number = ft_itoa(i);
	if (!file_number)
		return (perror("error creating the file_number string"), NULL);
	heredoc_filename = ft_strjoin("heredocs/.heredoc_", file_number);
	free(file_number);
	if (!heredoc_filename)
		return (perror("error creating the herdoc_filename"), NULL);
	return (heredoc_filename);
}

bool	ft_fill_heredoc(char *heredoc_name, char *delimiter)
{
	char	*line;
	int		heredoc_fd;

	heredoc_fd = open(heredoc_name, O_CREAT | O_RDWR | O_TRUNC, RW_R__R__);
	if (heredoc_fd == -1)
		return (perror("error opening heredoc file writing"), false);
	if (ft_is_quotes_in_delimiter(delimiter) && !ft_remove_quotes_from_token(&delimiter))
		return (false);//check for error return and adjust the function remove quotes
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
			break ;
		ft_putendl_fd(line, heredoc_fd);
		free(line);
	}
	ft_free_pointer_and_set_to_null((void **)&line);
	close(heredoc_fd);
	return (true);
}

bool	ft_is_quotes_in_delimiter(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (ft_is_char_quote(string[i]))
			return (true);
		i++;
	}
	return (false);
}