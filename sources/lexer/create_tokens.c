/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:48:01 by cmenke            #+#    #+#             */
/*   Updated: 2023/07/23 19:05:44 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_create_tokens_for_sequence(char *command_line_read, t_list **tokens)
{
	char				*start;
	//what need to happen when there is a newline in the command line read?
	while (*command_line_read)
	{
		ft_skip_to_next_non_delimiter(&command_line_read);
		start = command_line_read;
		ft_find_next_token(&command_line_read, &start, tokens);
		//creates one token if the string would be at least 1
		if (start != command_line_read && !ft_create_one_token(start, command_line_read, tokens))
			return (false); //check what needs to be cleared
		// if (*command_line_read && *command_line_read != '\"' && *command_line_read != '\'')
		// 	command_line_read += 1;
	}
	return (true);
}

void	ft_skip_to_next_non_delimiter(char **command_line)
{
	while (ft_is_whitespace(**command_line))
		*command_line += 1;
}

bool	ft_is_whitespace(char c)
{
	return (c == '\t' || c == ' ');
}

//seaparates the string by spaces and opeartors
bool	ft_find_next_token(char **string, char **start, t_list **tokens)
{
	while (**string)
	{
		ft_skip_quote_block(string, false);
		if (**string == '<' || **string == '>' || **string == '|')
		{
			if (*start != *string)
			{
				if (!ft_create_one_token(*start, *string, tokens))
					return (false); //check what needs to be cleared#
				*start = *string;
			}
			ft_move_while_same_char(string, **string);
			break ;
		}
		if (**string == ' ' || **string == '\t') //add newline???
			break;
		if (**string)
			*string += 1;
	}
	return (true);
}


void	ft_skip_quote_block(char **string, bool	only_single_quotes)
{
	char	quote;

	while (**string == '\'' || (!only_single_quotes && **string == '\"'))
	{
		quote = '\'';
		if (**string == '\"' && !only_single_quotes)
			quote = '\"';
		while (++(*string) && **string != quote)
			;
		if (**string && **string == quote)
			*string += 1;
	}
}

void	ft_move_while_same_char(char **command_line, char c)
{
	while (**command_line == c)
		*command_line += 1;
}

bool	ft_create_one_token(char *start, char *end, t_list **tokens)
{
	t_tokens	*token;
	t_list		*new_node;
	int			len;
	char		*string;

	token = ft_calloc(1, sizeof(t_tokens));
	if (!token)
	{
		ft_lstclear(tokens, ft_clear_token);
		return (false);
	}
	len = end - start;
	string = ft_substr(start, 0, len);
	if (!string)
	{
		//think about where to clear the things
		ft_lstclear(tokens, ft_clear_token);
		return (perror("error creatin string for token"), false);
	}
	token->token = string;
	new_node = ft_lstnew((void *)token);
	if (!new_node)
	{
		ft_lstclear(tokens, ft_clear_token);
		free(string);
		return (false);
	}
	ft_lstadd_back(tokens, new_node);
	return (true);
}
