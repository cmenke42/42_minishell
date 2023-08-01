/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:25:41 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/01 14:50:54 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_assign_token_type(void *node)
{
	t_tokens	*token;

	token = (t_tokens *)node;
	token->type = ft_get_token_type(token->token);
}

char	ft_get_token_type(char *string)
{
	int		len;
	char	first_character;

	len = ft_strlen(string);
	first_character = string[0];
	if (first_character == '<')
		return (ft_get_redirection_in_type(len));
	else if (first_character == '>')
		return (ft_get_redirection_out_type(len));
	else if (first_character == '|')
		return (ft_get_pipe_operator_type(len));
	else
		return (text);
}

char	ft_get_redirection_in_type(int len)
{
	if (len == 1)
		return (redirection_in);
	else if (len == 2)
		return (redirection_in_heredoc);
	else
		return (syntax_error);
}

char	ft_get_redirection_out_type(int len)
{
	if (len == 1)
		return (redirection_out_trunc);
	else if (len == 2)
		return (redirection_out_append);
	else
		return (syntax_error);
}

char	ft_get_pipe_operator_type(int len)
{
	if (len == 1)
		return (pipe_operator);
	else
		return (syntax_error);
}
