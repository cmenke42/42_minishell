/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_analysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:37:05 by user              #+#    #+#             */
/*   Updated: 2023/06/21 19:45:13 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// //When to print the error?
// //when to stop processing the commands?
// //when to continue processing the commands?

int	ft_is_operator(char c, int token_len)
{
	if (c == '|' && token_len == 1)
		return (op_pipe);
	else if (c == '|' && token_len > 1)
		return (token_error);
	if (c == '<' && token_len == 1)
		return (op_input_redirection);
	else if (c == '<' && token_len == 2)
		return (op_here_doc);
	else if (c == '<' && token_len > 2)
		return (token_error);
	if (c == '>' && token_len == 1)
		return (op_output_redirection_trunc);
	else if (c == '>' && token_len == 2)
		return (op_output_redirection_append);
	else if (c == '>' && token_len > 2)
		return (token_error);
	if (token_len > 0)
		return (enum_word);
	return (token_error);
}

int	ft_get_id_type(t_tokens *token)
{
	int	token_len;

	token_len = ft_strlen(token->token);
	return (ft_is_operator(token->token[0], token_len));

}

bool	ft_put_id_to_token(t_data *data)
{
	t_tokens *token;

	token = data->tokens;
	while (token)
	{
		token->token_type = ft_get_id_type(token);	
		token = token->next;
	}
	return (true);
}

//syntax error check for the tokens

bool	ft_operator_word_order(t_tokens *token)
{
	bool word;

	word = false;
	while (token)
	{	if (token->token_type == word)
			word = true;
		if (token->token_type == op_pipe && word == false)
			return (ft_putstr_fd(L_RED "#1 - Error near " STYLE_DEF, 2), ft_putendl_fd(token->token, 2), false);
		else if (token->token_type == op_pipe && word == true)
			word = false;
		if ((token->token_type >= 4 && token->token_type <= 7)
			&& ((token->next && token->next->token_type != enum_word) || !token->next))
			return (ft_putstr_fd(L_RED "#2 - Error near " STYLE_DEF, 2), ft_putendl_fd(token->token, 2), false);
		token = token->next;
	}
	return (true);
}

bool	ft_syntax_in_tokens(t_data *data)
{
	t_tokens *token;

	token = data->tokens;
	while (token)
	{
		if (token->token_type == token_error)
			return (ft_putstr_fd(L_RED "#3 - Error near " STYLE_DEF, 2), ft_putendl_fd(token->token, 2), false);

		token = token->next;
	}
	if (ft_operator_word_order(data->tokens) == false)
		return (false);
	token = data->tokens;
	while (token)
	{
		if (token->token_type == op_pipe && !token->next)
		{
			//add input to the existing comman line
			printf(BOLD_YELLOW "start reading for inoput\n" STYLE_DEF);
			return (false);
		}
		else if (token->token_type == op_pipe && token->next && token->next->token_type == op_pipe)
			return (ft_putstr_fd(L_RED "#4 - Error near " STYLE_DEF, 2), ft_putendl_fd(token->token, 2), false);
		token = token->next;
	}
	return (true);
}