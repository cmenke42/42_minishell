/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:59:19 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/26 12:18:39 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//If there is a quote it searches for the next quote of the same type.
//If there is not a second quote of the same type this means the ammount of 
//quotes is not equal.
int	ft_check_equal_quote_amt(char *s)
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
				return (ft_putendl_fd(L_RED SQUOTE_ERROR STYLE_DEF, 2), __syntax_error);
		}
		else if (s[i] == '\"')
		{
			while (s[++i] && s[i] != '\"')
				;
			if (s[i] != '\"')
				return (ft_putendl_fd(L_RED DQUOTE_ERROR STYLE_DEF, 2), __syntax_error);
		}
		if (s[i])
			i++;
	}
	return (__success);
}

bool	ft_search_and_print_syntax_error(t_shell_data *shell_data)
{
	t_list		*temp;
	t_tokens	*token;
	t_tokens	*next_token;

	temp = shell_data->all_tokens;
	while (temp)
	{
		token = (t_tokens *)temp->content;
		if (temp->next)
			next_token = (t_tokens *)temp->next->content;
		else
			next_token = NULL;
		if (ft_check_for_syntax_error(token, next_token))
			return (true);
		temp = temp->next;
	}
	return (false);
}

bool	ft_check_for_syntax_error(t_tokens *token, t_tokens *next_token)
{
	if (token->type == syntax_error)
	{	
		ft_print_syntax_error(next_token);
		return (true);
	}
	else if (ft_is_operator(token->type) && (!next_token || ft_is_operator(next_token->type)))
	{
		if (token->type == pipe_operator && !next_token) // change this to be an error
		{
			ft_print_syntax_error(next_token);

			return (true);
		}
		else if (token->type == pipe_operator && next_token)
			return (false);
		else
		{
			ft_print_syntax_error(next_token);
			return (true);
		}
	}
	return (false);
}

bool	ft_is_operator(char token_type)
{
	if (token_type >= 1 && token_type <= 6)
		return (true);
	return (false);
}

void	ft_print_syntax_error(t_tokens *next_token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (next_token)
		ft_putstr_fd(next_token->token, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
}