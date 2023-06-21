/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:26:23 by cmenke            #+#    #+#             */
/*   Updated: 2023/06/21 18:30:25 by cmenke           ###   ########.fr       */
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
bool	ft_create_one_token(t_data *data, char *line_read, int len, int *start)
{
	char		*token;
	t_tokens	*new_token;
	t_tokens	*last_token;

	int i = 0;
	printf(BOLD_GREEN "substr:\n" STYLE_DEF);
	while (i < len)
		printf("%c", line_read[i++]);
	printf(BOLD_GREEN "\nEND\n" STYLE_DEF);
	token = ft_substr(line_read, 0, len);
	if (!token)
		return (perror("malloc token substr creation"), false);
	new_token = ft_calloc(1, sizeof(t_tokens));
	if (!new_token)
		return (perror("malloc token node creation"), free(token), false);
	new_token->token = token;
	new_token->token_index = data->token_index++;
	last_token = data->tokens;
	while (last_token && last_token->next)
		last_token = last_token->next;
	if (last_token)
		last_token->next = new_token;
	else
		data->tokens = new_token;
	*start = *start + len;
	return (true);
}

void ft_skip_to_next_non_delim(char *line_read, int *i, int *start)
{
	while (line_read[*i] && (line_read[*i] == ' '
		|| line_read[*i] == '\t' || line_read[*i] == '\n'))
		*start = ++(*i);
}

//split up the command into tokens.
//|, <, >, space, tab, newline.
// when to check for = sign? or when to interpret this?
bool	ft_create_tokens(t_data *data, char *line_read)
{
	int		start;
	int		end;
	char	sign;
	bool	newline;

	printf(BOLD_PINK "token ceation start\n\n" STYLE_DEF);
	//check for syntax errors in the command line
	if (ft_check_equal_quote_amt(line_read) == false)
	{
		//check what needs to happen if there are multiple comman lines at once.
		data->finished_input = true;
		return (false);
	}
	end = 0;
	start = 0;
	newline = false;
	ft_skip_to_next_non_delim(line_read, &end, &start);
	while (line_read[end] && newline == false)
	{
		if (line_read[end] == '\'' || line_read[end] == '\"')
			ft_skip_quote_block(line_read, &end);
		else if (line_read[end] == '<' || line_read[end] == '>'	
			|| line_read[end] == '|')
		{
			if (end - start > 0)
				if (ft_create_one_token(data, &line_read[start], end - start, &start) == false)
					return (false);
			printf("current char: %c\n", line_read[end]);
			sign = line_read[end];
			if (line_read[end] == sign)
			{
				//how to handel the here_doc? especially when there is already input in the nex line.
				while (line_read[end] == sign)
					end++;
				printf("start: %d end: %d len: %d\n", start, end, end - start);
				printf("current char: %c\n", line_read[end]);
				if (end - start > 0)
				{
					if (ft_create_one_token(data, &line_read[start], end - start, &start) == false)
						return (false);
				}
				ft_skip_to_next_non_delim(line_read, &end, &start);
			}
		}
		else if (line_read[end] == ' ' || line_read[end] == '\t'
			|| line_read[end] == '\n')
		{
			if (ft_create_one_token(data, &line_read[start], end - start, &start) == false)
				return (false);
			if (line_read[end] == '\n')
			{
				newline = true;
				break ;
			}
			ft_skip_to_next_non_delim(line_read, &end, &start);
		}
		else
			end++;
	}
	if (newline == false && end - start > 0)
	{
		data->finished_input = true;
		if (ft_create_one_token(data, &line_read[start], end - start, &start) == false)
			return (false);
	}
	else if (newline == true)
	{
		//start executing this line.
		//then go on with the next one
		if (line_read[end + 1] != '\0')
			data->line_read = line_read + end + 1;
		else
			data->finished_input = true;
		//call the function that executes the command line.
		data->finished_input = true;
	}
	// When there is space at the end of the comand line
	data->finished_input = true;
	printf(BOLD_PINK "tokens created\n\n" STYLE_DEF);


	if (ft_put_id_to_token(data) == false)
	{
		printf("error in put id to token\n");
		return (false);
	}
	const char* tokenNames[] = {
    "word",
    "command",
    "single_quote",
    "double_quote",
    "op_input_red",
    "op_here_doc",
    "op_out_red_trunc",
    "op_out_red_append",
    "op_pipe",
    "op_variable_expansion",
    "token_error"
};

	t_tokens *temp;
	t_tokens *temp2;
	int i = 0;
	temp2 = data->tokens;
	while (data->tokens)
	{
		printf("token %d:" BOLD_BLUE"##"STYLE_DEF "Type:"BOLD_GREEN"%s	" STYLE_DEF BOLD_BLUE"##"STYLE_DEF"%s"BOLD_BLUE"##\n"STYLE_DEF, i++, tokenNames[data->tokens->token_type], data->tokens->token);
		temp = data->tokens;
		data->tokens = data->tokens->next;
		// free(temp);
	}
	data->tokens = temp2;
	return (true);
}