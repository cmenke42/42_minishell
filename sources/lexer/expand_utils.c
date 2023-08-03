/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:25:07 by wmoughar          #+#    #+#             */
/*   Updated: 2023/08/03 22:45:25 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_count_length(char *new_string, int *count, char c);
static void	ft_copy_char(char *new_string, int *count, char c);
static void	ft_process_string_to_trim(char *string, char *result, int *count,
				void (*copy_or_count)(char *, int *, char));

bool	ft_trim_value(char **string)
{
	char	*new_string;
	int		len;

	len = 0;
	if (!*string)
		return (true);
	ft_process_string_to_trim(*string, NULL, &len, ft_count_length);
	if (len == (int)ft_strlen(*string))
		return (true);
	new_string = malloc((len + 1) * sizeof(char));
	if (!new_string)
		return (perror("malloc - trim variable value"), false);
	new_string[len] = '\0';
	ft_process_string_to_trim(*string, new_string, NULL, ft_copy_char);
	free(*string);
	*string = new_string;
	return (true);
}

static void	ft_process_string_to_trim(char *string, char *result, int *count,
				void (*copy_or_count)(char *, int *, char))
{
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	while (string[i])
	{
		start = i;
		ft_skip_whitespace(string, &i);
		if (string[i] && start > 0 && start != i)
			copy_or_count(result + j++, count, ' ');
		if (string[i])
			copy_or_count(result + j++, count, string[i++]);
	}
}

void	ft_skip_whitespace(char *string, int *i)
{
	while (string[*i] && (ft_is_whitespace(string[*i])
			|| string[*i] == '\n')) //what about the new line???
		*i += 1;
}

static void	ft_count_length(char *new_string, int *count, char c)
{
	(void)new_string;
	(void)c;
	(*count)++;
}

static void	ft_copy_char(char *new_string, int *count, char c)
{
	(void)count;
	*new_string = c;
}
