/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:25:41 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/12 14:43:59 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_print_tokens_and_type(t_list *tokens)
{
	t_list		*temp;
	t_tokens	*token;

	temp = tokens;
	while (temp)
	{
		token = (t_tokens *)temp->content;
		ft_printf("token: %s, type: %d\n", token->token, token->type);
		temp = temp->next;
	}
	return ;
}

//checking the oder -> operator - no operator
bool	ft_is_syntax_error(t_shell_data *shell_data)
{
	t_list	*tokens;

	tokens = shell_data->all_tokens;
	// ft_print_token_list(shell_data->all_tokens);
	ft_lstiter(tokens, ft_set_token_types);
	ft_print_tokens_and_type(shell_data->all_tokens);
	ft_lstclear(&shell_data->all_tokens, ft_clear_token);
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
	char	type;

	len = ft_strlen(string);
	i = 0;
	first_character = string[0];
	//	making a if else tree to determine the token type
	// if (first_character ==)
	return (type);
}
