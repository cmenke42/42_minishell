/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_analysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:37:05 by user              #+#    #+#             */
/*   Updated: 2023/06/21 18:08:00 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// bool	ft_operator_in_token_unkown(t_tokens *token)
// {
// 	int		token_len;

// 	token_len = ft_strlen(token->token);

// }

// //When to print the error?
// //when to stop processing the commands?
// //when to continue processing the commands?
// bool	ft_syntax_error_in_tokens(t_data *data)
// {
// 	t_tokens *token;

// 	token = data->tokens;
// 	while (token)
// 	{
// 		token = token->next;
// 	}
// }

// bool	ft_analyze_tokens(t_data *data)
// {

// }

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
		return (word);
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