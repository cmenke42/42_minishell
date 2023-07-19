/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:07:55 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/19 18:05:56 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes(char *delimiter)
{
	while (*delimiter)
	{
		if (*delimiter == "\'" || *delimiter == "\"")
			return (1);
		delimiter++;
	}
	return (0);
}


char	*expand_line(char *line, t_env *env_list)
{
	t_tokens	*token;
	char		*str;

	token = (t_tokens *)malloc(sizeof(t_tokens));
	if (!token)
		return (NULL);
	token->token = line;
	ft_expand_variable((t_tokens *)token, env_list);
	str = token->token;
	free(token);
	return (str);
}

void	create_heredoc(t_tokens *command, int fd)
{
	char	*line;
	char	*test_fd = open(".heredoc_", O_CREAT | O_RDWR | O_TRUNC , RW_R__R__);
	int		heredoc_num = 1;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (!ft_strncmp(line, command->token, ft_strlen(command->token)))
			break;
		if (check_quotes(command->token) == 1)
			ft_remove_quotes_from_token(command->token);
		printf("%s\n", command->token);
		ft_putendl_fd(line, test_fd);
		//ft_putendl_fd(line, fd);
		
		free(line);
	}
	if (line)
		free(line);
	close(test_fd);
}
