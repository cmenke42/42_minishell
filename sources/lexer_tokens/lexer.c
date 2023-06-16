/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:26:23 by cmenke            #+#    #+#             */
/*   Updated: 2023/06/16 23:03:58 by cmenke           ###   ########.fr       */
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
				return (ft_putendl_fd(L_RED SQUOTE_ERROR STYLE_DEF, 2), false);
		}
		else if (s[i] == '\"')
		{
			while (s[++i] && s[i] != '\"')
				;
			if (s[i] != '\"')
				return (ft_putendl_fd(L_RED DQUOTE_ERROR STYLE_DEF, 2), false);
		}
		if (s[i])
			i++;
	}
	return (true);
}

bool	ft_create_one_token(t_data *data, char *line_read, int len)
{
	char		*token;
	t_tokens	*new_token;
	t_tokens	*last_token;

	token = ft_substr(line_read, 0, len);
	if (!token)
		return (false);
	new_token = ft_calloc(1, sizeof(t_tokens));
	if (!new_token)
		return (free(token), false);
	new_token->token = token;
	new_token->token_index = data->token_index++;
	last_token = data->tokens;
	while (last_token && last_token->next)
		last_token = last_token->next;
	if (last_token)
		last_token->next = new_token;
	else
		data->tokens = new_token;
	return (true);
}

//split up the command into tokens
//|, <, >, space, tab, newline.
// when to check for = sign? or when to interpret this?
bool	ft_create_tokens(t_data *data, char *line_read)
{
	int	start;
	int	end;

	end = 0;
	//check for syntax errors in the command line
	if (ft_check_equal_quote_amt(line_read) == false)
		return (false);
	while (line_read[end])
	{
		start = end;
		while (line_read[end])
		{
			if (line_read[start] == '\'' || line_read[start] == '\"')
			{
				printf("quote\n");
			}
			else if (line_read[start] == '<'|| line_read[start] == '>' || line_read[start] == '|' 
				|| line_read[start] == '=')
			{
				printf("special char\n");
			}
			else if (line_read[start] == ' ' || line_read[start] == '\t' || line_read[start] == '\n')
			{
				printf("space\n");
			}
			else
			{
				printf("normal char\n");
			}
			end++;
		}
		if (ft_create_one_token(data, line_read + start, end - start) == false)
			return (false);
	}
	printf("%s\n", "tokens created");
	t_tokens *temp;
	while (data->tokens)
	{
		printf("content of tokens: %s\n", data->tokens->token);
		temp = data->tokens;
		data->tokens = data->tokens->next;
		free(temp);
	}
	return (true);
}
