/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:38:02 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/20 09:48:45 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//pass string as reference
char	*ft_remove_quotes_from_token(char *token)
{
	int		counter;
	int		j;
	char	*new_line;

	j = 0;
	counter = ft_strlen_without_quotes(token);
	new_line = malloc((counter + 1) * sizeof(char));
	if (!new_line)
	{
		perror("malloc - remove quotes from elements");
		return (false);
	}
	ft_copy_element_without_quotes(token, new_line);
	free(token);
	token = new_line;
	return (token);
}

int	ft_strlen_without_quotes(char *cmd_line)
{
	char	quote;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '\'' || cmd_line[i] == '\"')
		{
			quote = '\"';
			if (cmd_line[i] == '\'')
				quote = '\'';
			while (cmd_line[++i] && cmd_line[i] != quote)
					count++;
			if (cmd_line[i] && cmd_line[i] == quote)
				i++;
		}
		if (cmd_line[i] && cmd_line[i] != '\'' && cmd_line[i] != '\"')
		{
			i++;
			count++;
		}
	}
	return (count);
}

void	ft_copy_element_without_quotes(char *cmd_line, char *new_line)
{
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '\'' || cmd_line[i] == '\"')
		{
			quote = '\"';
			if (cmd_line[i] == '\'')
				quote = '\'';
			while (cmd_line[++i] && cmd_line[i] != quote)
					new_line[j++] = cmd_line[i];
			if (cmd_line[i] && cmd_line[i] == quote)
				i++;
		}
		if (cmd_line[i] && cmd_line[i] != '\'' && cmd_line[i] != '\"')
			new_line[j++] = cmd_line[i++];
	}
	new_line[j] = '\0';
}