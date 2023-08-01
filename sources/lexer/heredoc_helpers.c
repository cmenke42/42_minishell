/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:47:48 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/01 15:50:59 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

bool	ft_expand_variables_in_heredoc_line(char **line,
			t_shell_data *shell_data)
{
	char	*string;

	string = *line;
	while (*string)
	{
		if (*string == '$')
		{
			if (!ft_execute_specific_case_of_variable_expansion(&string,
					line, false, shell_data))
			{
				return (false); //maybe clear something
			}
		}
		else
			string += 1;
	}
	return (true);
}
