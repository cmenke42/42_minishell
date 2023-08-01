/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:38:02 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/01 23:43:30 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_process_quote_string(char *string, char *new_string,
				void (*copy_or_count)(char *, char *, int *), int *count);
static void	ft_count_length(char *string, char *new_string, int *count);
static void	ft_copy_char(char *string, char *new_string, int *count);

//pass string as reference
bool	ft_remove_quotes_from_string(char **string)
{
	int		len;
	char	*new_string;

	len = 0;
	ft_process_quote_string(*string, NULL, ft_count_length, &len);
	if (len == (int)ft_strlen(*string))
		return (true);
	new_string = malloc((len + 1) * sizeof(char));
	if (!new_string)
		return (perror("malloc - remove quotes from elements"), false);
	new_string[len] = '\0';
	ft_process_quote_string(*string, new_string, ft_copy_char, NULL);
	free(*string);
	*string = new_string;
	return (true);
}

static void	ft_process_quote_string(char *string, char *new_string,
		void (*copy_or_count)(char *, char *, int *), int *count)
{
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote = '\0';
	while (string[i])
	{
		if (string[i] == '\'' || string[i] == '\"')
		{
			quote = string[i];
			while (string[++i] && string[i] != quote)
				copy_or_count(string + i, new_string + j++, count);
			if (string[i])
				i++;
		}
		else
			copy_or_count(string + i++, new_string + j++, count);
	}
}

static void	ft_count_length(char *string, char *new_string, int *count)
{
	(void)string;
	(void)new_string;
	(*count)++;
}

static void	ft_copy_char(char *string, char *new_string, int *count)
{
	(void)count;
	*new_string = *string;
}
