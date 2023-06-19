/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_analysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:37:05 by user              #+#    #+#             */
/*   Updated: 2023/06/19 22:40:38 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_operator_in_token_unkown(t_tokens *token)
{
	int		token_len;

	token_len = ft_strlen(token->token);

}

//When to print the error?
//when to stop processing the commands?
//when to continue processing the commands?
bool	ft_syntax_error_in_tokens(t_data *data)
{
	t_tokens *token;

	token = data->tokens;
	while (token)
	{
		token = token->next;
	}
}

bool	ft_analyze_tokens(t_data *data)
{

}