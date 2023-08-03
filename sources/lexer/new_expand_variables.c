/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_expand_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:30:24 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/03 22:40:36 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_get_expansion_case(char **string, bool in_double_quotes)
{
	char	next_char;

	next_char = *(*string + 1);
	if (ft_is_whitespace(next_char)
		|| (in_double_quotes && ft_is_char_quote(next_char)) || !next_char)
	{
		(*string)++;
		return (v_keep_dollar);
	}
	if (next_char == '$')
	{
		(*string) += 2;
		return (v_keep_dollar);
	}
	else if ((next_char) == '?')
		return (v_exit_code);
	else if (in_double_quotes)
		return (v_untrimmed_value);
	else
		return (v_trim_value);
}

//at least remove the dollar
//otherwise replace the name with the value
bool	ft_replace_name_with_value(char **string, char **token,
		char *variable_name, char *variable_value)
{
	int		variable_name_len;
	int		variable_value_len;
	int		total_len;
	char	*new_string;

	variable_name_len = 1;
	variable_value_len = 0;
	if (variable_name)
		variable_name_len += ft_strlen(variable_name);
	if (variable_value)
		variable_value_len = ft_strlen(variable_value);
	total_len = ft_strlen(*token) - variable_name_len + variable_value_len;
	new_string = malloc(sizeof(char) * (total_len + 1));
	if (!new_string)
		return (perror("error replacing variable name with value"), false);
	ft_strlcpy(new_string, *token, *string - *token + 1);
	if (variable_value)
		ft_strlcat(new_string, variable_value, total_len + 1);
	ft_strlcat(new_string, *string + variable_name_len, total_len + 1);
	free(*token);
	*token = new_string;
	*string = new_string;
	return (true);
}
