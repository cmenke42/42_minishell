/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:26:23 by cmenke            #+#    #+#             */
/*   Updated: 2023/06/16 01:22:26 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//If there is a quote it searches for the next quote of the same type.
//If there is not a second quote of the same type this means the ammount of 
//quotes is not equal.
bool	ft_check_equal_quote_amt(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			while (s[++i] && s[i] != '\'')
				;
			if (s[i] != '\'')
				return (false);
		}
		else if (s[i] == '\"')
		{
			while (s[++i] && s[i] != '\"')
				;
			if (s[i] != '\"')
				return (false);
		}
		if (s[i])
			i++;
	}
	return (true);
}

//split up the command into tokens
//|, <, >, space, tab, newline.

bool	ft_create_tokens(t_data *data, char *line_read)
{
	if (ft_check_equal_quote_amt(line_read) == false)
		ft_putendl_fd(LIGHT_RED QUOTE_ERROR STYLE_DEFAULT, STDERR_FILENO);
	
}

//check for syntax errors in the command line