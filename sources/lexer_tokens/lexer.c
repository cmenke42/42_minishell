/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:26:23 by cmenke            #+#    #+#             */
/*   Updated: 2023/06/17 00:22:52 by cmenke           ###   ########.fr       */
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

//skips a block of chars which is inbetween two quotes of the same type.
void	ft_skip_quote_block(char *cmd_line, int *i)
{
	char	quote;

	while (cmd_line[*i] && (cmd_line[*i] == '\'' || cmd_line[*i] == '\"'))
	{
		quote = '\"';
		if (cmd_line[*i] == '\'')
			quote = '\'';
		while (cmd_line[++(*i)] && cmd_line[*i] != quote)
			;
		if (cmd_line[*i] && cmd_line[*i] == quote)
			*i += 1;
	}
}

//This function creates a token and adds it to the linked list of tokens.
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

void ft_skip_to_next_non_delim(char *line_read, int *i)
{
	while (line_read[*i] && (line_read[*i] == ' '
		|| line_read[*i] == '\t' || line_read[*i] == '\n'))
		*i += 1;
}

//split up the command into tokens.
//|, <, >, space, tab, newline.
// when to check for = sign? or when to interpret this?
bool	ft_create_tokens(t_data *data, char *line_read)
{
	int	start;
	int	end;

	end = 0;
	printf(BOLD_PINK "token ceation start\n\n" STYLE_DEF);
	//check for syntax errors in the command line
	if (ft_check_equal_quote_amt(line_read) == false)
		return (false);
	while (line_read[end])
	{
		ft_skip_to_next_non_delim(line_read, &end);
		start = end;
		while (line_read[end])
		{
			if (line_read[end] == '\'' || line_read[end] == '\"')
			{
				printf("quote start %d\n", end);
				ft_skip_quote_block(line_read, &end);
				printf("quote end %d\n", end);
			}
			else if (line_read[end] == '<' || line_read[end] == '>' || line_read[end] == '|' 
				|| line_read[end] == '=')
			{
				printf("special char\n");
			}
			else if (line_read[end] == ' ' || line_read[end] == '\t' || line_read[end] == '\n')
			{
				printf("space\n");
				if (ft_create_one_token(data, line_read + start, end - start) == false)
					return (false);
				ft_skip_to_next_non_delim(line_read, &end);
				start = end;
				continue;
			}
			else
			{
				printf("normal char\n");
				end++;
			}
		}
		if (ft_create_one_token(data, line_read + start, end - start) == false)
			return (false);
	}
	printf(BOLD_PINK "tokens created\n\n" STYLE_DEF);
	t_tokens *temp;
	int i = 0;
	while (data->tokens)
	{
		printf("token %d: %s##\n", i++, data->tokens->token);
		temp = data->tokens;
		data->tokens = data->tokens->next;
		free(temp);
	}
	return (true);
}
