/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:25:41 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/23 17:17:17 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//checking the oder -> operator - no operator
bool	ft_is_syntax_error(t_shell_data *shell_data)
{
	t_list	*tokens;

	tokens = shell_data->all_tokens;
	ft_lstiter(tokens, ft_set_token_types);
	ft_search_and_print_syntax_error(shell_data);
	// ft_lstclear(&shell_data->all_tokens, ft_clear_token);
	return (false);
}

void	ft_set_token_types(void *node)
{
	t_tokens	*token;

	token = (t_tokens *)node;
	token->type = ft_get_token_type(token->token);
}

char	ft_get_token_type(char *string)
{
	int		len;
	int		i;
	char	first_character;

	len = ft_strlen(string);
	i = 0;
	first_character = string[0];
	if (first_character == '<')
	{
		if (len == 1)
			return (redirection_in);
		else if (len == 2)
			return (redirection_in_heredoc);
		else
			return (syntax_error);	
	}
	else if (first_character == '>')
	{
		if (len == 1)
			return (redirection_out_trunc);
		else if (len == 2)
			return (redirection_out_append);
		else
			return (syntax_error);
	}
	else if (first_character == '|')
	{
		if (len == 1)
			return (pipe_operator);
		else
			return (syntax_error);
	}
	else
		return (text);
}
