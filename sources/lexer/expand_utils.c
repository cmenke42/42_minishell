/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmoughar <wmoughar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:25:07 by wmoughar          #+#    #+#             */
/*   Updated: 2023/07/18 10:40:06 by wmoughar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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