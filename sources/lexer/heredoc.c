/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:07:55 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/23 17:36:53 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	create_heredoc(t_tokens *command)
{
	char	*line;
	int		tmp_fd;

	tmp_fd = open(".heredoc_", O_CREAT | O_RDWR | O_TRUNC, RW_R__R__);
	if (check_quotes(command))
		command->token = ft_remove_quotes_from_token(&command->token);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, command->token, ft_strlen(line)))
			break ;
		ft_putendl_fd(line, tmp_fd);
		free(line);
	}
	if (line)
		free(line);
	close(tmp_fd);
	return (open(".heredoc_", O_RDONLY));
}
